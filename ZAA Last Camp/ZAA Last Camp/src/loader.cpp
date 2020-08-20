#include "loader.h"

#include <glew.h>
#include <freeglut.h>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>

#include "lodepng\lodepng.h"
#include "console.h"
#include "rawMesh.h"
#include "sprite.h"
#include "texturedMesh.h"
#include "texture.h"


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
int vecContains(std::vector<int> &vec, int &value) {
	for (unsigned int i = 0; i < vec.size(); i++) {
		if (vec[i] == value) return i;
	}
	return -1;
}
/*
Loader class
*/

//constructor
Loader::Loader() {}

//models
void Loader::bindVBO(int index, std::vector<float> &data, int dataSize) {
	//create VBO
	GLuint vboID;
	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	VBOs.push_back(vboID);


	//bind data
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * data.size(), &data[0], GL_STATIC_DRAW);
	glVertexAttribPointer(index, dataSize, GL_FLOAT, GL_FALSE, 0, 0);
	
	//unbind VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}
RawMesh Loader::loadToVAO(std::vector<float> positions, std::vector<float> texCoords, std::vector<float> normals, std::vector<int> indexBuffer) {
	//creating the VAO
	GLuint vaoID = 0;
	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);
	VAOs.push_back(vaoID);
	
	//Element array buffer
	GLuint vboID;
	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indexBuffer.size(), &indexBuffer[0], GL_STATIC_DRAW);
	VBOs.push_back(vboID);

	//bind VBOs
	bindVBO(0, positions, 3);
	bindVBO(1, texCoords, 2);
	bindVBO(2, normals, 3);

	//unbind VAO
	glBindVertexArray(0);

	RawMesh rawMesh(vaoID, indexBuffer.size());
	return rawMesh;
}
TexturedMesh Loader::loadMesh(const char *filePath, const char *imagePath, const bool defaultPath) {
	//return values
	TexturedMesh texturedMesh;

	//opening the FileStream
	std::ifstream fileStream;
	fileStream.open((defaultPath) ? resPath + filePath : filePath);

	//error check
	if (!fileStream.is_open()) {
		console::err("Loader: unable to open: ", filePath);
		return texturedMesh;
	}

	//util Values
	RawMesh rawMesh;
	Texture texture = loadTexture(imagePath);
	std::string line;

	//unsorted
	std::vector<float> vertices_unsorted;
	std::vector<float> textureCoords_unsorted;
	std::vector<float> normalVertices_unsorted;

	while (!fileStream.eof()) {
		std::getline(fileStream, line);

		//vertices
		if (startWith(line, "v ", 2)) {
			std::vector<std::string> str = split(line, " ");
			for (unsigned int i = 1; i < str.size(); i++) {
				vertices_unsorted.push_back((float)atof(str[i].c_str()));
			}
			continue;
		}
		//textureCoords
		if (startWith(line, "vt", 2)) {
			std::vector<std::string> str = split(line, " ");

			textureCoords_unsorted.push_back((float)atof(str[1].c_str()));
			textureCoords_unsorted.push_back((float)atof(str[2].c_str()));

			continue;
		}
		//normalVertices
		if (startWith(line, "vn", 2)) {
			std::vector<std::string> str = split(line, " ");

			normalVertices_unsorted.push_back((float)atof(str[1].c_str()));
			normalVertices_unsorted.push_back((float)atof(str[2].c_str()));
			normalVertices_unsorted.push_back((float)atof(str[3].c_str()));

			continue;
		}
		//indices
		if (startWith(line, "f", 1)) {
			break;
		}
	}

	//indexes
	std::vector<int> position_Index;
	std::vector<int> nomals_Index;
	std::vector<int> texCoords_Index;
	std::vector<int> index;

	//string 
	bool read = false;
	while (!fileStream.eof()) {
		if (read) {
			std::getline(fileStream, line);
		}
		else {
			read = true;
		}
		if (!startWith(line, "f", 1)) continue;
		std::vector<std::string> splstr = split(line, " ");
		for (unsigned int i = 1; i < splstr.size(); i++) {
			std::vector<std::string> str = split(splstr[i], "/");

			//indexes
			int vertexIndex = atoi(str[0].c_str()) - 1;
			int textureIndex = atoi(str[1].c_str()) - 1;
			int normalIndex = atoi(str[2].c_str()) - 1;
			int currentIndex = vecContains(position_Index, vertexIndex);

			if (currentIndex == -1) {
				position_Index.push_back(vertexIndex);
				nomals_Index.push_back(normalIndex);
				texCoords_Index.push_back(textureIndex);
				index.push_back(position_Index.size() - 1);
			}
			else {
				if (texCoords_Index[currentIndex] == textureIndex) {
					index.push_back(currentIndex);
				}
				else {
					position_Index.push_back(vertexIndex);
					nomals_Index.push_back(normalIndex);
					texCoords_Index.push_back(textureIndex);
					index.push_back(position_Index.size() - 1);
				}
			}
		}
	}
	//sort the vectors
	unsigned int vertexIndexes = position_Index.size();
	std::vector<float> positions_sorted(vertexIndexes * 3);
	std::vector<float> textureCoords_sorted(vertexIndexes * 2);
	std::vector<float> normals_sorted(vertexIndexes * 3);
	for (unsigned int i = 0; i < vertexIndexes; i++) {

		//positions
		positions_sorted[i * 3] = vertices_unsorted[position_Index[i] * 3];
		positions_sorted[i * 3 + 1] = vertices_unsorted[position_Index[i] * 3 + 1];
		positions_sorted[i * 3 + 2] = vertices_unsorted[position_Index[i] * 3 + 2];

		//texture Coordianten
		textureCoords_sorted[i * 2] = textureCoords_unsorted[texCoords_Index[i] * 2];
		textureCoords_sorted[i * 2 + 1] = textureCoords_unsorted[texCoords_Index[i] * 2 + 1];

		//normalVectors
		normals_sorted[i * 3] = normalVertices_unsorted[nomals_Index[i] * 3];
		normals_sorted[i * 3 + 1] = normalVertices_unsorted[nomals_Index[i] * 3 + 1];
		normals_sorted[i * 3 + 2] = normalVertices_unsorted[nomals_Index[i] * 3 + 2];
	}

	rawMesh = loadToVAO(positions_sorted, textureCoords_sorted, normals_sorted, index);

	//ending the method
	fileStream.close();
	texturedMesh = TexturedMesh(rawMesh, texture);
	return texturedMesh;
}

//textures
Texture Loader::loadTexture(const char *filePath, const bool defaultPath) {
	//createing textureID
	GLuint textureID = 0;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	//load the pixels
	Sprite sprite = loader::loadSprite(filePath, defaultPath);

	//loading the pixels to the TextureID
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, sprite.getWidth(), sprite.getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, &(sprite.getPixels()[0]));

	glBindTexture(GL_TEXTURE_2D, 0);
	textures.push_back(textureID);
	return textureID;
}

//util
void Loader::cleanUp() {
	//VBOs
	for (unsigned int i = 0; i < VBOs.size(); i++) {
		glDeleteBuffers(1, &VBOs[i]);
	}
	console::log("Loader: Deleted VBOs", 1);

	//VAOs
	for (unsigned int i = 0; i < VAOs.size(); i++) {
		glDeleteBuffers(1, &VAOs[i]);
	}
	console::log("Loader: Deleted VAOs", 1);

	//Textures
	for (unsigned int i = 0; i < textures.size(); i++) {
		glDeleteTextures(1, &textures[i]);
	}
	console::log("Loader: Deleted Textures", 1);
}

/*
namespace
*/
std::string loader::readFile(const char *filePath, const bool defaultPath) {
	std::string content;
	std::ifstream fileStream;
	std::string file = (defaultPath) ? resPath + filePath : filePath;
	fileStream.open(file);

	//error check
	if (!fileStream.is_open()) {
		console::err("Loader: Could now read or open file", filePath);
		return " ";
	}

	//reading lines
	std::string line;
	while (!fileStream.eof()) {
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	//ending the method
	fileStream.close();
	return content;
}

//textures
Sprite loader::loadSprite(const char *filePath, const bool defaultPath) {
	std::vector<unsigned char> buffer;
	std::vector<unsigned char> image;
	unsigned width, height;

	lodepng::load_file(buffer, (defaultPath) ? resPath + filePath : filePath);

	unsigned error = lodepng::decode(image, width, height, buffer);

	if (error) {
		console::err("Loader: unabel to load: ", filePath, ". with following error", lodepng_error_text(error));
	}

	Sprite sprite(image, width, height);
	return sprite;
}