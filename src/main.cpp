#include <iostream>
#include <string>

#include <cassert>
#include <cstring>
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>


#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include "Image.h"
#include "Rays.h"

// This allows you to skip the `std::` in front of C++ standard library
// functions. You can also say `using std::cout` to be more selective.
// You should never do this in a header file.
using namespace std;



double RANDOM_COLORS[7][3] = {
	{0.0000,    0.4470,    0.7410},
	{0.8500,    0.3250,    0.0980},
	{0.9290,    0.6940,    0.1250},
	{0.4940,    0.1840,    0.5560},
	{0.4660,    0.6740,    0.1880},
	{0.3010,    0.7450,    0.9330},
	{0.6350,    0.0780,    0.1840},
};

int main(int argc, char **argv)
{
	if(argc < 2) {
		cout << "Usage: A1 meshfile" << endl;
		return 0;
	}
	string meshName(argv[1]);
	string output_name(argv[2]);
		int width = 1000;
		int height = 1000;
		int task;
		shared_ptr<Image> image = make_shared<Image>(width, height);
	// Load geometry
	vector<float> posBuf; // list of vertex positions
	vector<float> norBuf; // list of vertex normals
	vector<float> texBuf; // list of vertex texture coords
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	string errStr;
	bool rc = tinyobj::LoadObj(&attrib, &shapes, &materials, &errStr, meshName.c_str());
	if(!rc) {
		cerr << errStr << endl;
	} else {
		// Some OBJ files have different indices for vertex positions, normals,
		// and texture coordinates. For example, a cube corner vertex may have
		// three different normals. Here, we are going to duplicate all such
		// vertices.
		// Loop over shapes
		for(size_t s = 0; s < shapes.size(); s++) {
			// Loop over faces (polygons)
			size_t index_offset = 0;
			for(size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
				size_t fv = shapes[s].mesh.num_face_vertices[f];
				// Loop over vertices in the face.
				for(size_t v = 0; v < fv; v++) {
					// access to vertex
					tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
					posBuf.push_back(attrib.vertices[3*idx.vertex_index+0]);
					posBuf.push_back(attrib.vertices[3*idx.vertex_index+1]);
					posBuf.push_back(attrib.vertices[3*idx.vertex_index+2]);
					if(!attrib.normals.empty()) {
						norBuf.push_back(attrib.normals[3*idx.normal_index+0]);
						norBuf.push_back(attrib.normals[3*idx.normal_index+1]);
						norBuf.push_back(attrib.normals[3*idx.normal_index+2]);
					}
					if(!attrib.texcoords.empty()) {
						texBuf.push_back(attrib.texcoords[2*idx.texcoord_index+0]);
						texBuf.push_back(attrib.texcoords[2*idx.texcoord_index+1]);
					}
				}
				index_offset += fv;
				// per-face material (IGNORE)
				shapes[s].mesh.material_ids[f];
			}
		}
	}
	cout << "Number of vertices: " << posBuf.size()/3 << endl;

//chooses the scene dependent on the integer passed thorguh
	switch (stoi(argv[1]))
	{
		//just testing hit detection
	case 1:
	{	
		vector<vec3> rays = Ray_gen(vec3(0.0,0.0,5.0),vec3(0.0,0.0,4.0),width,height);
		//printf("size is %d \n", (int) rays.size());

		Ellipsoid sus (vec3(0.0,0.0,0.0),vec3(1.0,0.0,0.0),vec3(0.1,0.1,0.1),vec3(1.0,1.0,0.5),100.0);

	for(int i = 0 ; i < (int)rays.size() ;i++){
		//printf("ray at %d,%d is vec3 (%f,%f,%f)\n",i/3,i%3,rays.at(i).x,rays.at(i).y,rays.at(i).z);

		vector<vec3> result = sus.single_raytrace(rays.at(i),vec3(0,0,5));

		//printf(" results are distance %f and hit position %f,%f,%f\n\n\n", result.at(0).x, result.at(1).x,result.at(1).y,result.at(1).z);
		
		if(result.at(0).x >= 0){
			image->setPixel(i/width,i%height,0,0,100 + 10 * result.at(0).x);
		}
		else{
			image->setPixel(i/width,i%height,0,0,0);
		}
	 }
	 break;
	}
	case 2:
	{

	break;
	}
		
	
	case 3:
	{

		

	}

	default:
		break;
	}
		//writes out the image to certain filename.
	image->writeToFile("TEST_output.png");
	return 0;
}
