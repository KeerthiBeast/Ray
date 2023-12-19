#ifndef THREADRENDER_H
#define THREADRENDER_H

#include "rtweekend.h"
#include "camera.h"
#include "sphere.h"
#include "material.h"
#include "sphere.h"

#include <cstring>
#include <string>
#include <float.h>
#include <iostream>
#include <condition_variable>

#include <fstream>
#include <chrono>
#include <string>

#include <thread>
#include <mutex>
#include <vector>
#include <atomic>
#include <queue>

std::mutex writeM;

struct BlockJob {
    int row_start = 0;
    int row_end = 0;
    int col_size;
    std::vector<int> indices;
    std::vector<vec3> colors;
};

void render(camera cam, BlockJob job, const hittable& world, std::vector<BlockJob>& imageblocks, std::mutex& mutex,
std::condition_variable& cv)
{
    for(int j=job.row_start; j<job.row_end; ++j)
    {
        for(int i=0; i<job.col_size; ++i)
        {
            color pixel_color(0,0,0);
            for(int sample=0; sample < cam.samples_per_pixel; ++sample)
            {
                ray r = cam.get_ray(i, j);
                pixel_color += cam.ray_color(r, cam.max_depth, world);
            }
            pixel_color /= float(cam.samples_per_pixel);
            pixel_color = vec3(sqrt(pixel_color[0]), sqrt(pixel_color[1]), sqrt(pixel_color[2]));
            static const interval intensity(0.000, 0.999);
            pixel_color = vec3(intensity.clamp(pixel_color[0]), intensity.clamp(pixel_color[1]),
            intensity.clamp(pixel_color[2]));

            const unsigned int index = j * job.col_size + i;
            job.indices.push_back(index);
            job.colors.push_back(pixel_color);
        }
    }
    std::lock_guard<std::mutex> lock(mutex);
    imageblocks.push_back(job);
}

void ThreadJobLoop(
	camera cam,const hittable& world,
	std::queue<BlockJob>& jobQ, 
	std::vector<BlockJob>& finishedJobs, 
	std::mutex& mutex,
	std::condition_variable& cv
	)
{
	std::atomic<bool> hasWork{ true };
	while (hasWork)
	{
		BlockJob job;
		{
			std::lock_guard<std::mutex> lock(mutex);
			if (!jobQ.empty())
			{
				job = jobQ.front();
				jobQ.pop();
			}
		}
		// quick/dirty way to find if a job is valid
		if (job.row_start < job.row_end)
		{
			render(cam, job, world, finishedJobs,  mutex, cv);
		}
		else
		{
			hasWork = false;
		}
	}

	// no more jobs.
	{
		std::lock_guard<std::mutex> lock(mutex);
		cv.notify_one();
	}
}

void imagerender(const camera& cam, const hittable& world) {
    int size = cam.pixelcount;
    vec3* image = new vec3[size];
    memset(&image[0], 0, size * sizeof(vec3));

    auto fulltime = std::chrono::high_resolution_clock::now();
    const int nThreads = std::thread::hardware_concurrency();
    int nRowsPerJob = 200;
    int nJobs = cam.image_height / nRowsPerJob; // 1 row per job
    int leftOver = cam.image_height % nThreads;

    std::mutex mutex;
    std::condition_variable cvres;
    std::vector<BlockJob> imageblocks;
    std::queue<BlockJob> jobqueue;
    std::vector<std::thread> threads;

    for (int i = 0; i < nJobs; ++i) {
        BlockJob job;
        job.row_start = i * nRowsPerJob;
        job.row_end = job.row_start + nRowsPerJob;
        if (i == nThreads - 1)
        {
            job.row_end = job.row_start + nRowsPerJob + leftOver;
        }
        job.col_size = cam.image_width;

        jobqueue.push(job);
    }

    for (int i = 0; i < nThreads - 1; ++i) {
        std::thread t([&]() {
            ThreadJobLoop(cam, world, jobqueue, imageblocks, mutex, cvres);
        });
        threads.push_back(std::move(t));
    }

    ThreadJobLoop(cam, world, jobqueue, imageblocks, mutex, cvres);
    std::unique_lock<std::mutex> lock(mutex);
    cvres.wait(lock, [&imageblocks, &nJobs] {
        return imageblocks.size() == nJobs;});

    for (std::thread& t : threads) {
        t.join();
    }

    for (BlockJob job : imageblocks) {
        int colorIndex = 0;
        for (vec3& col : job.colors)
        {
            int colIndex = job.indices[colorIndex];
            image[colIndex] = col;
            ++colorIndex;
        }
    }

    std::cout<< "P3\n" << cam.image_width << " " << cam.image_height << "\n255\n";

    for (unsigned int i = 0; i < cam.image_width * cam.image_height; ++i)
    {
        // BGR to RGB
        // 2 = r;
        // 1 = g;
        // 0 = b;
        // static const interval intensity(0.000, 0.999);
        std::cout << static_cast<int>(255.99f * (image[i].e[0])) << " "
            << static_cast<int>(255.99f * (image[i].e[1])) << " "
            << static_cast<int>(255.99f * (image[i].e[2])) << "\n";
    }
}
#endif