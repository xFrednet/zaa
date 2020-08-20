#include <glew.h>
#include <algorithm>
#include <freeglut.h>
#include <fstream>
#include <iostream>
#include <SOIL.h>
#include <stdio.h>
#include <string>
#include <vec2.hpp>
#include <vec3.hpp>
#include <vector>

#include "debug.h"
#include "loader.h"
#include "LoadPNG\lodepng.h"

/*	##################
* 	# Help Functions #
*   ################## */
bool startWith(std::string str, std::string str2, int count) {
	for (int i = 0; i < count; i++) {
		if (str[i] != str2[i]) return false;
	}
	return true;
}
std::vector<std::string> split(std::string str, std::string delimiter) {
	std::vector<std::string> returnStr;

	size_t pos = 0;
	while ((pos = str.find(delimiter)) != std::string::npos) {
		returnStr.push_back(str.substr(0, pos));
		str.erase(0, pos + delimiter.length());
	}
	returnStr.push_back(str);
	return returnStr;
}

/*	###############
 * 	# VAOs / VBOs #
 *  ############### */

//VAO
GLuint Loader::createVAO() {
	GLuint vaoID = 0;
	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);
	VAOs.push_back(vaoID);
	return vaoID;
}
void Loader::unbindVAO() {
	glBindVertexArray(0);
}

//VBO
void Loader::storeDataInAttributeList(int attributeNumber, int coordinateSize, const float data[], const int VertexIndexes) {
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * VertexIndexes * coordinateSize, data, GL_STATIC_DRAW);
	glVertexAttribPointer(attributeNumber, coordinateSize, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	VBOs.push_back(VBO);
}
void Loader::bindIndicesBuffer(const int indices[], const int vertexCount) {
	GLuint vboID;
	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * vertexCount, indices, GL_STATIC_DRAW);
	
	VBOs.push_back(vboID);
}

//Models
RawModel Loader::loadToVAO(const float positions[], const float texturePositions[], const float normals[], const int VertexIndexes, const int indices[], const int vertexCount) {
	
	GLuint VAO = createVAO();
	bindIndicesBuffer(indices, vertexCount);
	storeDataInAttributeList(0, 3, positions, VertexIndexes);
	storeDataInAttributeList(1, 2, texturePositions, VertexIndexes);

	unbindVAO();
	RawModel model(VAO, vertexCount);
	return model;
}
TexturedModel Loader::loadModel(const char *filePath) {
	RawModel rawModel;
	ModelTexture modelTexture;
	TexturedModel model;

	//file stream
	std::ifstream fileStream(filePath, std::ios::in);
	if (!fileStream.is_open()) {
		console::err("Could not load Model from file ", filePath);
		return model;
	}

	//unsorted
	std::vector<float> vertices;
	std::vector<float> textureCoords_unsorted;
	std::vector<float> normalVertices_unsorted;

	std::string line;
	while (!fileStream.eof()) {
		std::getline(fileStream, line);

		//vertices
		if (startWith(line, "v ", 2)) {
			std::vector<std::string> str = split(line, " ");
			for (unsigned int i = 1; i < str.size(); i++) {
				vertices.push_back((float)atof(str[i].c_str()));
			}
			continue;
		}
		//textureCoords
		if (startWith(line, "vt", 2)){
			std::vector<std::string> str = split(line, " ");
			
			textureCoords_unsorted.push_back((float)atof(str[1].c_str()));
			textureCoords_unsorted.push_back((float)atof(str[2].c_str()));

			continue;
		} 
		//normalVertices
		if (startWith(line, "vn", 2)) {
			std::vector<std::string> str = split(line, " ");
			
			normalVertices_unsorted.push_back((float)atof(str[2].c_str()));
			normalVertices_unsorted.push_back((float)atof(str[3].c_str()));
			
			continue;
		}
		//indices
		if (startWith(line, "usemtl", 6)) {
			std::vector<std::string> str = split(line, " ");
			modelTexture = loadTexture(str[1].c_str());
			continue;
		}

		if (startWith(line, "f", 1)) {
			break;
		}
	}

	//sorted
	int VertexIndexes = vertices.size() / 3;
	std::vector<float> textureCoords(VertexIndexes * 20);
	std::vector<float> normals(VertexIndexes * 30);
	std::vector<int> indices;
	bool read = false;
	while (!fileStream.eof()) {
		if (read) {
			std::getline(fileStream, line);
		}
		else {
			read = true;
		}
		if (startWith(line, "f", 1)) {
			std::vector<std::string> splstr = split(line, " ");
			for (unsigned int i = 1; i < splstr.size(); i++) {
				std::vector<std::string> str = split(splstr[i], "/");
				int vertexIndex = atoi(str[0].c_str()) - 1;
				indices.push_back(vertexIndex);

				//texture Coordianten
				int textureIndex = atoi(str[1].c_str()) - 1;
				textureCoords[vertexIndex * 2] = textureCoords_unsorted[textureIndex * 2];
				textureCoords[vertexIndex * 2 + 1] = textureCoords_unsorted[textureIndex * 2 + 1];

				int normalIndex = atoi(str[2].c_str()) - 1;
				normalVertices_unsorted.push_back((float)atof(str[1].c_str()));
				//normalVectors
				normals[vertexIndex * 2] = normalVertices_unsorted[normalIndex * 3];
				normals[vertexIndex * 2 + 1] = normalVertices_unsorted[normalIndex * 3 + 1];
				normals[vertexIndex * 2 + 2] = normalVertices_unsorted[normalIndex * 3 + 2];

			}
		}
	}

	rawModel = loadToVAO(&vertices[0], &textureCoords[0], &normals[0], VertexIndexes, &indices[0], indices.size());
	model = TexturedModel(rawModel, modelTexture);
	fileStream.close();
	return model;
}

/*	###########
* 	# Texture #
*   ########### */

Sprite Loader::loadImage(const char *fileName) {
	std::vector<unsigned char> buffer;
	std::vector<unsigned char> image;
	unsigned width, height;
	
	lodepng::load_file(buffer, fileName);
	unsigned error = lodepng::decode(image, width, height, buffer);
	if (error) {
		console::err("Loader: unabel to load: ", fileName, ". with following error", lodepng_error_text(error));

	}

	Sprite sprite(image, width, height);
	return sprite;
}
GLuint Loader::loadTexture(const char *filename) {
	GLuint image = 0;
	glGenTextures(1, &image);
	glBindTexture(GL_TEXTURE_2D, image);

	Sprite s = loadImage(filename);
	
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, s.width, s.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &s.pixels[0]);

	glBindTexture(GL_TEXTURE_2D, 0);
	textureIDs.push_back(image);
	return image;
}

/*	#########
* 	# Other #
*   ######### */

std::string Loader::readFile(std::string filePath) {
	std::string content;
	std::ifstream fileStream(filePath, std::ios::in);
	
	if (!fileStream.is_open()) {
		console::err("Could not read or open file ", filePath);
		return "";
	}

	std::string line;
	while (!fileStream.eof()) {
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;
}
void Loader::cleanUp() {
	//Deleting VBOs
	for (unsigned int i = 0; i < VBOs.size(); i++) {
		glDeleteBuffers(1, &VBOs[i]);
	}
	if (DEBUG > 1)
		console::log("Loader: Deleted ", (int) VBOs.size(), " VBOS", 2);
	else 
		console::log("Loader: Deleted VBOS", 1);

	//Deleting VAOs
	for (unsigned int i = 0; i < VAOs.size(); i++) {
		glDeleteVertexArrays(1, &VAOs[i]);
	}
	if (DEBUG > 1)
		console::log("Loader: Deleted ", (int)VAOs.size(), " VAOS", 2);
	else
		console::log("Loader: Deleted VAOS", 1);

	//testures
	for (unsigned int i = 0; i < textureIDs.size(); i++) {
		glDeleteTextures(1, &textureIDs[i]);
	}
	if (DEBUG > 1)
		console::log("Loader: Deleted ", (int)textureIDs.size(), " Textures", 2);
	else
		console::log("Deleted Textures", 1);
}