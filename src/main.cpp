#include <iostream>
#include <string>

#include <cassert>
#include <cstring>
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <threads>

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
		cout << "Usage: ./A6 <scene> <image size> <image filename>" << endl;
		return 0;
	}
	
	string meshName("placeholder");
	string output_name(argv[3]);
		int width = stoi(argv[2]);
		int height = stoi(argv[2]);
		//int scene;
		shared_ptr<Image> image = make_shared<Image>(width, height);
	//only loads object in if we are doing scene 6 or scene 7
	 if(stoi(argv[1]) >= 6){
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
	}
	//initalize the rays and objects to be used for the multiple scenes
	vector<Object*> objects;
	vector<vec3> rays = Ray_gen(vec3(0.0,0.0,5.0),vec3(0.0,0.0,4.0),height,width);
	vector<vec3> light_pos;
	vector<vec3> light_color;

	//chooses the scene dependent on the integer passed thorguh
	switch (stoi(argv[1]))
	{
		//just testing hit detection
	case 1:
	{	
		
		light_pos.push_back(vec3(-2.0, 1.0, 1.0));
		light_color.push_back(vec3(1.0,1.0,1.0));
		//generates
		objects.push_back(new Ellipsoid(vec3(-0.5, -1.0, 1.0),vec3(1.0,0.0,0.0),vec3(0.1,0.1,0.1),vec3(1.0,1.0,0.5),100.0));
		objects.push_back(new Ellipsoid(vec3(0.5, -1.0, -1.0),vec3(0.0,1.0,0.0),vec3(0.1,0.1,0.1),vec3(1.0,1.0,0.5),100.0));
		objects.push_back(new Ellipsoid(vec3(0.0, 1.0, 0.0),vec3(0.0,0.0,1.0),vec3(0.1,0.1,0.1),vec3(1.0,1.0,0.5),100.0));

	for(int n = 0 ; n < (int)rays.size() ;n++){
		//calls ray generation 
		vec3 color = ray_color_gen(rays.at(n),vec3(0.0,0.0,5.0),objects,light_pos,light_color,0);
		 color.x = (color.x *255 > 255)? 255 : color.x * 255;
		 color.y = (color.y*255 > 255)? 255 : color.y * 255;
		 color.z = (color.z*255 > 255)? 255 : color.z * 255;
		 //does this since we are starting at bottom left corner so x is incrementing col 0 to n while y is incrementing from row n to  0
		image->setPixel((n)%width,(rays.size() - 1 -n )/height,color.r,color.g,color.b);
		
	 }
	 break;
	}
	case 2:
	{

		light_pos.push_back(vec3(-2.0, 1.0, 1.0));
		light_color.push_back(vec3(1.0,1.0,1.0));
		//generates
		objects.push_back(new Ellipsoid(vec3(-0.5, -1.0, 1.0),vec3(1.0,0.0,0.0),vec3(0.1,0.1,0.1),vec3(1.0,1.0,0.5),100.0));
		objects.push_back(new Ellipsoid(vec3(0.5, -1.0, -1.0),vec3(0.0,1.0,0.0),vec3(0.1,0.1,0.1),vec3(1.0,1.0,0.5),100.0));
		objects.push_back(new Ellipsoid(vec3(0.0, 1.0, 0.0),vec3(0.0,0.0,1.0),vec3(0.1,0.1,0.1),vec3(1.0,1.0,0.5),100.0));

	for(int n = 0 ; n < (int)rays.size() ;n++){
		//calls ray generation 
		vec3 color = ray_color_gen(rays.at(n),vec3(0.0,0.0,5.0),objects,light_pos,light_color,1);
		 color.x = (color.x *255 > 255)? 255 : color.x * 255;
		 color.y = (color.y*255 > 255)? 255 : color.y * 255;
		 color.z = (color.z*255 > 255)? 255 : color.z * 255;
		 //does this since we are starting at bottom left corner so x is incrementing col 0 to n while y is incrementing from row n to  0
		image->setPixel((n)%width,(rays.size() - 1 -n )/height,color.r,color.g,color.b);
	}


	break;
	}
		
	
	case 3:
	{
		//adds the multiples lights for the scene
		light_pos.push_back(vec3(1.0, 2.0, 2.0));
		light_color.push_back(vec3(0.5,0.5,0.5));		
		light_pos.push_back(vec3(-1.0, 2.0, -1.0));
		light_color.push_back(vec3(0.5,0.5,0.5));

		//generates ellipsoid(for the ellipsoid use translate to ensure we move it before scaling) plane and sphere
		objects.push_back(new Ellipsoid(vec3(0.0,0.0,0.0),vec3(1.0,0.0,0.0),vec3(0.1,0.1,0.1),vec3(1.0,1.0,0.5),100.0,0,vec3(0.5,0.0,0.5),vec3(0.5, 0.6, 0.2)));
		objects.push_back(new Ellipsoid(vec3(-0.5, 0.0, -0.5),vec3(0.0,1.0,0.0),vec3(0.1,0.1,0.1),vec3(1.0,1.0,0.5),100.0));
		objects.push_back(new plane(vec3(0.0,1.0,0.0),vec3(0.0,-1.0,0.0),vec3(1.0,1.0,1.0),vec3(0.1,0.1,0.1),vec3(0,0,0),0.0));

		for(int n = 0 ; n < (int)rays.size() ;n++){
		//calls ray generation 
		vec3 color = ray_color_gen(rays.at(n),vec3(0.0,0.0,5.0),objects,light_pos,light_color,1);
		 color.x = (color.x *255 > 255)? 255 : color.x * 255;
		 color.y = (color.y*255 > 255)? 255 : color.y * 255;
		 color.z = (color.z*255 > 255)? 255 : color.z * 255;
		 //does this since we are starting at bottom left corner so x is incrementing col 0 to n while y is incrementing from row n to  0
		image->setPixel((n)%width,(rays.size() - 1 -n )/height,color.r,color.g,color.b);
	}
		
		break;
	}

	case 4:
	{
		//adds the multiples lights for the scene
		light_pos.push_back(vec3(-1.0, 2.0, 1.0));
		light_color.push_back(vec3(0.5,0.5,0.5));		
		light_pos.push_back(vec3(0.5, -0.5, 0.0));
		light_color.push_back(vec3(0.5,0.5,0.5));

		objects.push_back(new Ellipsoid(vec3(0.0,0.0,0.0),vec3(1.0,0.0,0.0),vec3(0.1,0.1,0.1),vec3(1.0,1.0,0.5),100.0,0,vec3(0.5, -0.7, 0.5),vec3(0.3, 0.3, 0.3)));
		objects.push_back(new Ellipsoid(vec3(0.0,0.0,0.0),vec3(0.0,0.0,1.0),vec3(0.1,0.1,0.1),vec3(1.0,1.0,0.5),100.0,0,vec3(1.0, -0.7, 0.0),vec3(0.3, 0.3, 0.3)));
		//reflective spheres
		objects.push_back(new Ellipsoid(vec3(0.0,0.0,0.0),vec3(0.0,0.0,0.0),vec3(0.0,0.0,0.0),vec3(0.0,0.0,0.0),100.0,1,vec3(-0.5, 0.0, -0.5)));
		objects.push_back(new Ellipsoid(vec3(0.0,0.0,0.0),vec3(0.0,0.0,0.0),vec3(0.0,0.0,0.0),vec3(0.0,0.0,0.0),100.0,1,vec3(1.5, 0.0, -1.5)));


		objects.push_back(new plane(vec3(0.0,0.0,1.0),vec3(0.0,0.0,-3.0),vec3(1.0,1.0,1.0),vec3(0.1,0.1,0.1),vec3(0,0,0),0.0));
		objects.push_back(new plane(vec3(0.0,1.0,0.0),vec3(0.0,-1.0,0.0),vec3(1.0,1.0,1.0),vec3(0.1,0.1,0.1),vec3(0,0,0),0.0));
		



		for(int n = 0 ; n < (int)rays.size() ;n++){
		//calls ray generation 
		vec3 color = ray_color_gen(rays.at(n),vec3(0.0,0.0,5.0),objects,light_pos,light_color,2);
		 color.x = (color.x *255 > 255)? 255 : color.x * 255;
		 color.y = (color.y*255 > 255)? 255 : color.y * 255;
		 color.z = (color.z*255 > 255)? 255 : color.z * 255;
		 //does this since we are starting at bottom left corner so x is incrementing col 0 to n while y is incrementing from row n to  0
		image->setPixel((n)%width,(rays.size() - 1 -n )/height,color.r,color.g,color.b);
		}
	break;
	}
	case 5:
	{
		//adds the multiples lights for the scene
		light_pos.push_back(vec3(-1.0, 2.0, 1.0));
		light_color.push_back(vec3(0.5,0.5,0.5));		
		light_pos.push_back(vec3(0.5, -0.5, 0.0));
		light_color.push_back(vec3(0.5,0.5,0.5));

		objects.push_back(new Ellipsoid(vec3(0.0,0.0,0.0),vec3(1.0,0.0,0.0),vec3(0.1,0.1,0.1),vec3(1.0,1.0,0.5),100.0,0,vec3(0.5, -0.7, 0.5),vec3(0.3, 0.3, 0.3)));
		objects.push_back(new Ellipsoid(vec3(0.0,0.0,0.0),vec3(0.0,0.0,1.0),vec3(0.1,0.1,0.1),vec3(1.0,1.0,0.5),100.0,0,vec3(1.0, -0.7, 0.0),vec3(0.3, 0.3, 0.3)));
		//reflective spheres
		objects.push_back(new Ellipsoid(vec3(0.0,0.0,0.0),vec3(0.0,0.0,0.0),vec3(0.0,0.0,0.0),vec3(0.0,0.0,0.0),100.0,1,vec3(-0.5, 0.0, -0.5)));
		objects.push_back(new Ellipsoid(vec3(0.0,0.0,0.0),vec3(0.0,0.0,0.0),vec3(0.0,0.0,0.0),vec3(0.0,0.0,0.0),100.0,1,vec3(1.5, 0.0, -1.5)));


		objects.push_back(new plane(vec3(0.0,0.0,1.0),vec3(0.0,0.0,-3.0),vec3(1.0,1.0,1.0),vec3(0.1,0.1,0.1),vec3(0,0,0),0.0));
		objects.push_back(new plane(vec3(0.0,1.0,0.0),vec3(0.0,-1.0,0.0),vec3(1.0,1.0,1.0),vec3(0.1,0.1,0.1),vec3(0,0,0),0.0));
		



		for(int n = 0 ; n < (int)rays.size() ;n++){
		//calls ray generation 
		vec3 color = ray_color_gen(rays.at(n),vec3(0.0,0.0,5.0),objects,light_pos,light_color,3);
		 color.x = (color.x *255 > 255)? 255 : color.x * 255;
		 color.y = (color.y*255 > 255)? 255 : color.y * 255;
		 color.z = (color.z*255 > 255)? 255 : color.z * 255;
		 //does this since we are starting at bottom left corner so x is incrementing col 0 to n while y is incrementing from row n to  0
		image->setPixel((n)%width,(rays.size() - 1 -n )/height,color.r,color.g,color.b);
		}
	break;
	}
	case 6:
	{
		


	break;
	}
	case 7:
	{
	break;
	}



	default:
	printf("scenes 1 - 7 only available try again :)\n");
		exit(1);
		break;
	}
		//writes out the image to certain filename.
	image->writeToFile(output_name);
	return 0;
}
