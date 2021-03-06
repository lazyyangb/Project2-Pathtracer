// CIS565 CUDA Raytracer: A parallel raytracer for Patrick Cozzi's CIS565: GPU Computing at the University of Pennsylvania
// Written by Yining Karl Li, Copyright (c) 2012 University of Pennsylvania
// This file includes code from:
//       Yining Karl Li's TAKUA Render, a massively parallel pathtracing renderer: http://www.yiningkarlli.com

#ifndef CUDASTRUCTS_H
#define CUDASTRUCTS_H

#include "glm/glm.hpp"
#include "cudaMat4.h"
#include <cuda_runtime.h>
#include <string>
#include "utilities.h"
#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
enum GEOMTYPE{ SPHERE, CUBE, MESH };


struct ray {
	__host__ __device__ ray()
	{
		m_index = 1.0;
		tag = 1.0;
		color_fraction = 1.0;//keep track of how much this ray contribute the final color
	}
	glm::vec3 origin;
	glm::vec3 direction;
	int tag; // -1 if dead, 1 if alive
	int pixelId; //each ray stores the pixelId when been initialized
	float m_index;
	float color_fraction;
};
struct mesh{
	mesh()
	{
		triangleNum = 0;
		faceNum = 0;
	}
	int triangleNum;
	int faceNum;
	glm::vec3* boundingBox_min;
	glm::vec3* boundingBox_max;
	glm::vec3* pbo;
	glm::vec3* ibo;
	glm::vec3* nbo;
	//thrust::device_vector<glm::vec3> pbo;
};
struct geom {
	geom(){
		numberOfTriangle = 0;
	}
	enum GEOMTYPE type;
	int materialid;
	int frames;
	glm::vec3* translations;
	glm::vec3* rotations;
	glm::vec3* scales;
	cudaMat4* transforms;
	cudaMat4* inverseTransforms;
	int pboIndexOffset;
	int iboIndexOffset;
	int nboIndexOffset;
	int numberOfTriangle;
	glm::vec3* boundingBox_min;
	glm::vec3* boundingBox_max;
};

struct staticGeom {
	enum GEOMTYPE type;
	int materialid;
	glm::vec3 translation;
	glm::vec3 rotation;
	glm::vec3 scale;
	cudaMat4 transform;
	cudaMat4 inverseTransform;
	int pboIndexOffset;
	int iboIndexOffset;
	int nboIndexOffset;
	int numberOfTriangle;
	glm::vec3 boundingBox_min;
	glm::vec3 boundingBox_max;

};

struct cameraData {
	glm::vec2 resolution;
	glm::vec3 position;
	glm::vec3 view;
	glm::vec3 up;
	glm::vec2 fov;
};

struct camera {
	glm::vec2 resolution;
	glm::vec3* positions;
	glm::vec3* views;
	glm::vec3* ups;
	int frames;
	glm::vec2 fov;
	unsigned int iterations;
	glm::vec3* image;
	ray* rayList;
	std::string imageName;
};

struct material{
	glm::vec3 color;
	float specularExponent;
	glm::vec3 specularColor;
	float hasReflective;
	float hasRefractive;
	float indexOfRefraction;
	float hasScatter;
	glm::vec3 absorptionCoefficient;
	float reducedScatterCoefficient;
	float emittance;
};

#endif //CUDASTRUCTS_H
