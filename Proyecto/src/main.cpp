//Proyecto de semestre 2024-1
#define _USE_MATH_DEFINES
#include <cmath>
//glew include
#include <GL/glew.h>

//tiempo
#include<ctime>
#include<iostream>
//#include <unistd.h>
#include<windows.h>   

//std includes
#include <string>
#include <iostream>

//glfw include
#include <GLFW/glfw3.h>

// program include
#include "Headers/TimeManager.h"

// Shader include
#include "Headers/Shader.h"

// Model geometric includes
#include "Headers/Sphere.h"
#include "Headers/Cylinder.h"
#include "Headers/Box.h"
#include "Headers/FirstPersonCamera.h"
#include "Headers/ThirdPersonCamera.h"

// Font rendering include
#include "Headers/FontTypeRendering.h"

//GLM include
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Headers/Texture.h"

// Include loader Model class
#include "Headers/Model.h"

// Include Terrain
#include "Headers/Terrain.h"

#include "Headers/AnimationUtils.h"

// Include Colision headers functions
#include "Headers/Colisiones.h"

// ShadowBox include
#include "Headers/ShadowBox.h"

// OpenAL include
#include <AL/alut.h>


#include <chrono>


#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))

int screenWidth;
int screenHeight;
float MCScale = 0.01091f;
bool spiderCollision = false;
bool spiderCollision2 = false;
bool spiderCollision3 = false;
bool spiderCollision4 = false;
bool chairCollision = false;
bool playing = true;
bool psi = true;
int numCollisionsSpider;
bool isColision;
bool llave = false;
int v1 = rand() % 56;

int time_before_loop_begins = 0;
int time_after_loop_ends = 0;
std::string chairSets[56]  = {
	"Muebles","Muebles2","Muebles3","Muebles4","Muebles5","Muebles6","Muebles7","Muebles8","Muebles9","Muebles10",
	"Muebles11","Muebles12","Muebles13","Muebles14","Muebles15","Muebles16","Muebles17","Muebles18","Muebles19","Muebles20",
	"Muebles21","Muebles22","Muebles23","Muebles24","Muebles25","Muebles26","Muebles27","Muebles28","Muebles29","Muebles30",
	"Muebles31","Muebles32","Muebles33","Muebles34","Muebles35","Muebles36","Muebles37","Muebles38","Muebles39","Muebles40",
	"Muebles41","Muebles42","Muebles43","Muebles44","Muebles45","Muebles46","Muebles47","Muebles48","MueblesExt1","MueblesExt2",
	"MueblesExt3","MueblesExt4","MueblesExt5","MueblesExt6","MueblesExt7","MueblesExt8"
};
std::string spiderSets[5] = {
	"Spider", "Spider2", "Spider3", "Spider4", "Spider5"
};
std::string currentChair;
std::string textoNoticia = "Evita a las aranias, encuentra la llave y la salida.";



const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;

GLFWwindow *window;

Shader shader;
//Shader con skybox
Shader shaderSkybox;
//Shader con multiples luces
Shader shaderMulLighting;
//Shader para el terreno
Shader shaderTerrain;
// Shader para dibujar un objeto con solo textura
Shader shaderTexture;
//Shader para dibujar el buffer de profunidad
Shader shaderDepth;
// Shader para visualizar el buffer de profundidad
Shader shaderViewDepth;
//Shader para las particulas de fountain
Shader shaderParticlesFountain;

std::shared_ptr<Camera> camera(new ThirdPersonCamera());
float distanceFromTarget = 7.0;

Sphere skyboxSphere(20, 20);
Box boxCesped;
Box boxWalls;
Box boxHighway;
Box boxLandingPad;
Sphere esfera1(10, 10);
Box boxCollider;
Sphere sphereCollider(10, 10);
Cylinder rayModel(10, 10, 1.0, 1.0, 1.0);
Box boxIntro;
Box boxViewDepth;
// Models complex instances
Model modelRock;
Model modelTiendas1;
Model modelTiendas2;
Model modelBasura;
Model modelPared;
Model modelTecho;
Model modelMuebles;
Model modelTelevision1;
Model modelTelevision2;
Model modelTelevision3;
Model modelTiendasSalida;


// Modelos animados
// Main
Model mayowModelAnimate;
Model spiderModelAnimate;

// Terrain model instance
Terrain terrain(-1, -1, 200, 8, "../Elementos_proyecto/heightmap2.png");

ShadowBox * shadowBox;

GLuint textureCespedID, textureWallID, textureWindowID, textureHighwayID, textureLandingPadID;
GLuint textureTerrainRID, textureTerrainGID, textureTerrainBID, textureTerrainBlendMapID;
GLuint skyboxTextureID;
GLuint textureInit1ID, textureInit2ID, textureActivaID, textureScreenID, textureScreen3ID, textureScreen2ID, textureScreen1ID, textureScreenGOID, textureScreenWNID;
GLuint textureParticleFountainID;

bool iniciaPartida = false, presionarOpcion = false;

// Modelo para el render del texto
FontTypeRendering::FontTypeRendering *modelText;

GLenum types[6] = {
GL_TEXTURE_CUBE_MAP_POSITIVE_X,
GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
GL_TEXTURE_CUBE_MAP_NEGATIVE_Z };

std::string fileNames[6] = { "../Elementos_proyecto/skybox/all_black/black.jpg",
		"../Elementos_proyecto/skybox/all_black/black.jpg",
		"../Elementos_proyecto/skybox/all_black/black.jpg",
		"../Elementos_proyecto/skybox/all_black/black.jpg",
		"../Elementos_proyecto/skybox/all_black/black.jpg",
		"../Elementos_proyecto/skybox/all_black/black.jpg" };

bool exitApp = false;
int lastMousePosX, offsetX = 0;
int lastMousePosY, offsetY = 0;


// Model matrix definitions
glm::mat4 modelMatrixEclipse = glm::mat4(1.0f);
glm::mat4 matrixModelRock = glm::mat4(1.0);
glm::mat4 modelMatrixHeli = glm::mat4(1.0f);
glm::mat4 modelMatrixLambo = glm::mat4(1.0);
glm::mat4 modelMatrixAircraft = glm::mat4(1.0);
glm::mat4 modelMatrixDart = glm::mat4(1.0f);
glm::mat4 modelMatrixBuzz = glm::mat4(1.0f);

glm::mat4 modelMatrixCowboy = glm::mat4(1.0f);
glm::mat4 modelMatrixGuardian = glm::mat4(1.0f);
glm::mat4 modelMatrixFountain = glm::mat4(1.0f);

//Keep this matrixes
glm::mat4 modelMatrixMayow = glm::mat4(1.0f);
glm::mat4 modelMatrixSpider = glm::mat4(1.0f);
glm::mat4 modelMatrixSpider2 = glm::mat4(1.0f);
glm::mat4 modelMatrixSpider3 = glm::mat4(1.0f);
glm::mat4 modelMatrixSpider4 = glm::mat4(1.0f);
glm::mat4 modelMatrixSpider5 = glm::mat4(1.0f);
glm::mat4 matrixModelTiendas1 = glm::mat4(1.0);
glm::mat4 matrixModelTiendas1Ext = glm::mat4(1.0);
glm::mat4 matrixModelTiendas2 = glm::mat4(1.0);
glm::mat4 matrixModelTiendas2Ext = glm::mat4(1.0);
glm::mat4 matrixModelBasura = glm::mat4(1.0);
glm::mat4 matrixModelPared = glm::mat4(1.0);
glm::mat4 matrixModelTecho = glm::mat4(1.0);
glm::mat4 matrixModelTelevision1 = glm::mat4(1.0);
glm::mat4 matrixModelTelevision2 = glm::mat4(1.0);
glm::mat4 matrixModelTelevision3 = glm::mat4(1.0);
glm::mat4 matrixModelTiendasSalida = glm::mat4(1.0);
glm::mat4 matrixModelTelevision1Ext = glm::mat4(1.0);
glm::mat4 matrixModelTelevision2Ext = glm::mat4(1.0);
glm::mat4 matrixModelTelevision3Ext = glm::mat4(1.0);

//Matrices para el conjunto de sillas y mesas chicas
glm::mat4 matrixModelMuebles = glm::mat4(1.0);
glm::mat4 matrixModelMuebles2 = glm::mat4(1.0);
glm::mat4 matrixModelMuebles3 = glm::mat4(1.0);
glm::mat4 matrixModelMuebles4 = glm::mat4(1.0);
glm::mat4 matrixModelMuebles5 = glm::mat4(1.0);
glm::mat4 matrixModelMuebles6 = glm::mat4(1.0);
glm::mat4 matrixModelMuebles7 = glm::mat4(1.0);
glm::mat4 matrixModelMuebles8 = glm::mat4(1.0);
glm::mat4 matrixModelMuebles9 = glm::mat4(1.0);
glm::mat4 matrixModelMuebles10 = glm::mat4(1.0);
glm::mat4 matrixModelMuebles11 = glm::mat4(1.0);
glm::mat4 matrixModelMuebles12 = glm::mat4(1.0);
glm::mat4 matrixModelMuebles13 = glm::mat4(1.0);
glm::mat4 matrixModelMuebles14 = glm::mat4(1.0);
glm::mat4 matrixModelMuebles15 = glm::mat4(1.0);
glm::mat4 matrixModelMuebles16 = glm::mat4(1.0);

glm::mat4 matrixModelMuebles17 = glm::mat4(1.0);
glm::mat4 matrixModelMuebles18 = glm::mat4(1.0);
glm::mat4 matrixModelMuebles19 = glm::mat4(1.0);
glm::mat4 matrixModelMuebles20 = glm::mat4(1.0);

glm::mat4 matrixModelMuebles21 = glm::mat4(1.0);
glm::mat4 matrixModelMuebles22 = glm::mat4(1.0);
glm::mat4 matrixModelMuebles23 = glm::mat4(1.0);
glm::mat4 matrixModelMuebles24 = glm::mat4(1.0);
glm::mat4 matrixModelMuebles25 = glm::mat4(1.0);
glm::mat4 matrixModelMuebles26 = glm::mat4(1.0);
glm::mat4 matrixModelMuebles27 = glm::mat4(1.0);
glm::mat4 matrixModelMuebles28 = glm::mat4(1.0);
glm::mat4 matrixModelMuebles29 = glm::mat4(1.0);
glm::mat4 matrixModelMuebles30 = glm::mat4(1.0);
glm::mat4 matrixModelMuebles31 = glm::mat4(1.0);
glm::mat4 matrixModelMuebles32 = glm::mat4(1.0);
glm::mat4 matrixModelMuebles33 = glm::mat4(1.0);
glm::mat4 matrixModelMuebles34 = glm::mat4(1.0);
glm::mat4 matrixModelMuebles35 = glm::mat4(1.0);
glm::mat4 matrixModelMuebles36 = glm::mat4(1.0);
glm::mat4 matrixModelMuebles37 = glm::mat4(1.0);
glm::mat4 matrixModelMuebles38 = glm::mat4(1.0);
glm::mat4 matrixModelMuebles39 = glm::mat4(1.0);
glm::mat4 matrixModelMuebles40 = glm::mat4(1.0);
glm::mat4 matrixModelMuebles41 = glm::mat4(1.0);
glm::mat4 matrixModelMuebles42 = glm::mat4(1.0);
glm::mat4 matrixModelMuebles43 = glm::mat4(1.0);
glm::mat4 matrixModelMuebles44 = glm::mat4(1.0);
glm::mat4 matrixModelMuebles45 = glm::mat4(1.0);
glm::mat4 matrixModelMuebles46 = glm::mat4(1.0);
glm::mat4 matrixModelMuebles47 = glm::mat4(1.0);
glm::mat4 matrixModelMuebles48 = glm::mat4(1.0);
//Covers
glm::mat4 matrixModelMueblesExt1 = glm::mat4(1.0);
glm::mat4 matrixModelMueblesExt2 = glm::mat4(1.0);
glm::mat4 matrixModelMueblesExt3 = glm::mat4(1.0);
glm::mat4 matrixModelMueblesExt4 = glm::mat4(1.0);
glm::mat4 matrixModelMueblesExt5 = glm::mat4(1.0);
glm::mat4 matrixModelMueblesExt6 = glm::mat4(1.0);
glm::mat4 matrixModelMueblesExt7 = glm::mat4(1.0);
glm::mat4 matrixModelMueblesExt8 = glm::mat4(1.0);



int animationMayowIndex = 3;
int animationSpiderIndex = 1;
int animationSpiderIndex2 = 1;
int animationSpiderIndex3 = 1;
int animationSpiderIndex4 = 1;
int animationSpiderIndex5 = 0;
int modelSelected = 0;
bool enableCountSelected = true;
int playerLife = 4;

//mov ARAÑA1
int stateSpider1 = 0;
int numberAdvanceSpider = 0;
int maxAdvanceSpider = 0;
//velocidad
float avanceSpider = 0.80;
float rotSpider = 0.50;
float advanceCountSpider = 0;
float rotCountSpider = 0.0;

//mov ARAÑA2
int stateSpider2 = 0;
int numberAdvanceSpider2 = 0;
int maxAdvanceSpider2 = 0;
//velocidad
float avanceSpider2 = 0.6;
float rotSpider2 = 0.10;
float advanceCountSpider2 = 0;
float rotCountSpider2 = 0.0;

//mov ARAÑA3
int stateSpider3 = 0;
int numberAdvanceSpider3 = 0;
int maxAdvanceSpider3 = 0;
//velocidad
float avanceSpider3 = 0.40;
float rotSpider3 = 0.50;
float advanceCountSpider3 = 0;
float rotCountSpider3 = 0.0;

//mov ARAÑA4
int stateSpider4 = 0;
int numberAdvanceSpider4 = 0;
int maxAdvanceSpider4 = 0;
//velocidad
float avanceSpider4 = 0.40;
float rotSpider4 = 0.50;
float advanceCountSpider4 = 0;
float rotCountSpider4 = 0.0;

//mov ARAÑA5
int stateSpider5 = 0;
int numberAdvanceSpider5 = 0;
int maxAdvanceSpider5 = 0;
//velocidad
float avanceSpider5 = 0.40;
float rotSpider5 = 0.50;
float advanceCountSpider5 = 0;
float rotCountSpider5 = 0.0;

// Var animate
float rotHelHelY = 0.0;
float rotHelHelBack = 0.0;

// Lamps position
std::vector<glm::vec3> lamp1Position = {
	//PRIMERA TELEVISION
	glm::vec3(8.0f, 3.12f, -6.2f),
	glm::vec3(-8.5f, 3.12f, 39.1f),
	glm::vec3(-25.0f, 3.12f, -6.2f),
	//repeticion de telvision
	glm::vec3(-41.5f, 3.12f, 39.1f),
	glm::vec3(-58.0f, 3.12f, -6.2f),
	glm::vec3(-74.5f, 3.12f, 39.1f)

};
std::vector<float> lamp1Orientation = {
	-17.0, -82.67, 23.70
};
std::vector<glm::vec3> lamp2Position = {
	glm::vec3(-36.52, 0, -23.24),
	glm::vec3(-52.73, 0, -3.90)
};
std::vector<float> lamp2Orientation = {
	21.37 + 90, -65.0 + 90
};

// Blending model unsorted
std::map<std::string, glm::vec3> blendingUnsorted = {
		{"aircraft", glm::vec3(10.0, 0.0, -17.5)},
		{"lambo", glm::vec3(23.0, 0.0, 0.0)},
		{"heli", glm::vec3(5.0, 10.0, -5.0)}
};

double deltaTime;
double currTime, lastTime;


// Jump variables
bool isJump = false;
float GRAVITY = 5.81;
double tmv = 0;
double startTimeJump = 0;

// Colliders
std::map<std::string, std::tuple<AbstractModel::OBB, glm::mat4, glm::mat4> > collidersOBB;
std::map<std::string, std::tuple<AbstractModel::SBB, glm::mat4, glm::mat4> > collidersSBB;

// Variables animacion maquina de estados eclipse
const float avance = 0.1;
const float giroEclipse = 0.5f;
float rotWheelsX = 0.0;
float rotWheelsY = 0.0;

// OpenAL Defines
#define NUM_BUFFERS 6
#define NUM_SOURCES 6
#define NUM_ENVIRONMENTS 1
// Listener
ALfloat listenerPos[] = { 0.0, 0.0, 4.0 };
ALfloat listenerVel[] = { 0.0, 0.0, 0.0 };
ALfloat listenerOri[] = { 0.0, 0.0, 1.0, 0.0, 1.0, 0.0 };
// Source 0
ALfloat source0Pos[] = { -2.0, 0.0, 0.0 };
ALfloat source0Vel[] = { 0.0, 0.0, 0.0 };
// Source 1
ALfloat source1Pos[] = { 2.0, 0.0, 0.0 };
ALfloat source1Vel[] = { 0.0, 0.0, 0.0 };
// Source 2
ALfloat source2Pos[] = { 2.0, 0.0, 0.0 };
ALfloat source2Vel[] = { 0.0, 0.0, 0.0 };
// Source 3
ALfloat source3Pos[] = { 2.0, 0.0, 0.0 };
ALfloat source3Vel[] = { 0.0, 0.0, 0.0 };
// Source 4
ALfloat source4Pos[] = { 2.0, 0.0, 0.0 };
ALfloat source4Vel[] = { 0.0, 0.0, 0.0 };
// Source 5
ALfloat source5Pos[] = { 2.0, 0.0, 0.0 };
ALfloat source5Vel[] = { 0.0, 0.0, 0.0 };
// Buffers
ALuint buffer[NUM_BUFFERS];
ALuint source[NUM_SOURCES];
ALuint environment[NUM_ENVIRONMENTS];
// Configs
ALsizei size, freq;
ALenum format;
ALvoid *data;
int ch;
ALboolean loop;
std::vector<bool> sourcesPlay = {true, true, true};

// Framesbuffers
GLuint depthMap, depthMapFBO;

//Definición del framebuffer
GLuint initVel, startTime, VAOParticles, nParticles = 400;
double curTimeParticlesFountainAnimation, lastTimeParticlesFountainAnimation; 

// Se definen todos las funciones.
void reshapeCallback(GLFWwindow *Window, int widthRes, int heightRes);
void keyCallback(GLFWwindow *window, int key, int scancode, int action,
		int mode);
void mouseCallback(GLFWwindow *window, double xpos, double ypos);
void mouseButtonCallback(GLFWwindow *window, int button, int state, int mod);
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
void initParticleBuffers();
void init(int width, int height, std::string strTitle, bool bFullScreen);
void destroy();
bool processInput(bool continueApplication = true);



// Implementacion de todas las funciones.
void init(int width, int height, std::string strTitle, bool bFullScreen) {

	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW" << std::endl;
		exit(-1);
	}

	screenWidth = width;
	screenHeight = height;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	if (bFullScreen)
		window = glfwCreateWindow(width, height, strTitle.c_str(), glfwGetPrimaryMonitor(), nullptr);
	else
		window = glfwCreateWindow(width, height, strTitle.c_str(), nullptr, nullptr);

	if (window == nullptr) {
		std::cerr
				<< "Error to create GLFW window, you can try download the last version of your video card that support OpenGL 3.3+"
				<< std::endl;
		destroy();
		exit(-1);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(0);

	glfwSetWindowSizeCallback(window, reshapeCallback);
	glfwSetKeyCallback(window, keyCallback);
	glfwSetCursorPosCallback(window, mouseCallback);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);
	glfwSetScrollCallback(window, scrollCallback);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Init glew
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		std::cerr << "Failed to initialize glew" << std::endl;
		exit(-1);
	}

	glViewport(0, 0, screenWidth, screenHeight);
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	// Inicialización de los shaders
	shader.initialize("../Shaders/colorShader.vs", "../Shaders/colorShader.fs");
	shaderSkybox.initialize("../Shaders/skyBox.vs", "../Shaders/skyBox_fog.fs");
	shaderMulLighting.initialize("../Shaders/iluminacion_textura_animation_shadow.vs", "../Shaders/multipleLights_shadow.fs");
	shaderTerrain.initialize("../Shaders/terrain_shadow.vs", "../Shaders/terrain_shadow.fs");
	shaderTexture.initialize("../Shaders/texturizado.vs", "../Shaders/texturizado.fs");
	shaderViewDepth.initialize("../Shaders/texturizado.vs", "../Shaders/texturizado_depth_view.fs");
	shaderDepth.initialize("../Shaders/shadow_mapping_depth.vs", "../Shaders/shadow_mapping_depth.fs");
	shaderParticlesFountain.initialize("../Shaders/particlesFountain.vs", "../Shaders/particlesFountain.fs");

	// Inicializacion de los objetos.
	skyboxSphere.init();
	skyboxSphere.setShader(&shaderSkybox);
	skyboxSphere.setScale(glm::vec3(20.0f, 20.0f, 20.0f));

	boxCollider.init();
	boxCollider.setShader(&shader);
	//boxCollider.setColor(glm::vec4(1.0, 1.0, 1.0, 1.0));
	boxCollider.setColor(glm::vec4(0.0, 0.0, 0.0, 0.0));

	sphereCollider.init();
	sphereCollider.setShader(&shader);
	sphereCollider.setColor(glm::vec4(1.0, 1.0, 1.0, 1.0));

	rayModel.init();
	rayModel.setShader(&shader);
	rayModel.setColor(glm::vec4(1.0));

	boxCesped.init();
	boxCesped.setShader(&shaderMulLighting);

	boxWalls.init();
	boxWalls.setShader(&shaderMulLighting);

	boxHighway.init();
	boxHighway.setShader(&shaderMulLighting);

	boxLandingPad.init();
	boxLandingPad.setShader(&shaderMulLighting);

	esfera1.init();
	esfera1.setShader(&shaderMulLighting);

	boxIntro.init();
	boxIntro.setShader(&shaderTexture);
	boxIntro.setScale(glm::vec3(2.0, 2.0, 1.0));

	boxViewDepth.init();
	boxViewDepth.setShader(&shaderViewDepth);


	// Main
	mayowModelAnimate.loadModel("../Elementos_proyecto/main_animated/main_animated.fbx");
	mayowModelAnimate.setShader(&shaderMulLighting);

	//Araña
	spiderModelAnimate.loadModel("../Elementos_proyecto/spider/spider/spider.fbx");
	spiderModelAnimate.setShader(&shaderMulLighting);
	
	//Primeras tiendas, segmento más corto
	modelTiendas1.loadModel("../Elementos_proyecto/Tiendas_menor/tiendas_menor_ext.fbx");
	modelTiendas1.setShader(&shaderMulLighting);

	modelTiendas2.loadModel("../Elementos_proyecto/tiendas_mayor/tiendas_mayor_ext.fbx");
	modelTiendas2.setShader(&shaderMulLighting);

	modelBasura.loadModel("../Elementos_proyecto/trash/trash.fbx");
	modelBasura.setShader(&shaderMulLighting);

	modelPared.loadModel("../Elementos_proyecto/Ambiente/Paredes.fbx");
	modelPared.setShader(&shaderMulLighting);

	modelTecho.loadModel("../Elementos_proyecto/Ambiente/Techo.fbx");
	modelTecho.setShader(&shaderMulLighting);

	modelMuebles.loadModel("../Elementos_proyecto/Sillas_Mesas/sillas_mesas_cortas.fbx");
	modelMuebles.setShader(&shaderMulLighting);

	modelTelevision1.loadModel("../Elementos_proyecto/Ambiente/tv1.fbx");
	modelTelevision1.setShader(&shaderMulLighting);

	modelTelevision2.loadModel("../Elementos_proyecto/Ambiente/tv2.fbx");
	modelTelevision2.setShader(&shaderMulLighting);

	modelTelevision3.loadModel("../Elementos_proyecto/Ambiente/tv3.fbx");
	modelTelevision3.setShader(&shaderMulLighting);

	modelTiendasSalida.loadModel("../Elementos_proyecto/Ambiente/door.fbx");
	modelTiendasSalida.setShader(&shaderMulLighting);

	// Terreno
	terrain.init();
	terrain.setShader(&shaderTerrain);

	// Se inicializa el model de render text
	modelText = new FontTypeRendering::FontTypeRendering(screenWidth, screenHeight);
	modelText->Initialize();

	camera->setPosition(glm::vec3(0.0, 3.0, 4.0));
	camera->setDistanceFromTarget(distanceFromTarget);
	camera->setSensitivity(1.0);
	
	// Carga de texturas para el skybox
	Texture skyboxTexture = Texture("");
	glGenTextures(1, &skyboxTextureID);
	// Tipo de textura CUBE MAP
	glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTextureID);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	for (int i = 0; i < ARRAY_SIZE_IN_ELEMENTS(types); i++) {
		skyboxTexture = Texture(fileNames[i]);
		skyboxTexture.loadImage(true);
		if (skyboxTexture.getData()) {
			glTexImage2D(types[i], 0, skyboxTexture.getChannels() == 3 ? GL_RGB : GL_RGBA, skyboxTexture.getWidth(), skyboxTexture.getHeight(), 0,
			skyboxTexture.getChannels() == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, skyboxTexture.getData());
		} else
			std::cout << "Failed to load texture" << std::endl;
		skyboxTexture.freeImage();
	}

	// Definiendo la textura a utilizar
	Texture textureCesped("../Elementos_proyecto/Textures/tiles.png");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	textureCesped.loadImage();
	// Creando la textura con id 1
	glGenTextures(1, &textureCespedID);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureCespedID);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Verifica si se pudo abrir la textura
	if (textureCesped.getData()) {
		// Transferir los datos de la imagen a memoria
		// Tipo de textura, Mipmaps, Formato interno de openGL, ancho, alto, Mipmaps,
		// Formato interno de la libreria de la imagen, el tipo de dato y al apuntador
		// a los datos
		std::cout << "Numero de canales :=> " << textureCesped.getChannels() << std::endl;
		glTexImage2D(GL_TEXTURE_2D, 0, textureCesped.getChannels() == 3 ? GL_RGB : GL_RGBA, textureCesped.getWidth(), textureCesped.getHeight(), 0,
		textureCesped.getChannels() == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, textureCesped.getData());
		// Generan los niveles del mipmap (OpenGL es el ecargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	} else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	textureCesped.freeImage();

	// Defininiendo texturas del mapa de mezclas
	// Definiendo la textura
	Texture textureR("../Elementos_proyecto/Textures/mud.png");
	textureR.loadImage(); // Cargar la textura
	glGenTextures(1, &textureTerrainRID); // Creando el id de la textura del landingpad
	glBindTexture(GL_TEXTURE_2D, textureTerrainRID); // Se enlaza la textura
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Wrapping en el eje u
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Wrapping en el eje v
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Filtering de minimización
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Filtering de maximimizacion
	if(textureR.getData()){
		// Transferir los datos de la imagen a la tarjeta
		glTexImage2D(GL_TEXTURE_2D, 0, textureR.getChannels() == 3 ? GL_RGB : GL_RGBA, textureR.getWidth(), textureR.getHeight(), 0,
		textureR.getChannels() == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, textureR.getData());
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else 
		std::cout << "Fallo la carga de textura" << std::endl;
	textureR.freeImage(); // Liberamos memoria

	// Definiendo la textura
	Texture textureG("../Elementos_proyecto/Textures/grassFlowers.png");
	textureG.loadImage(); // Cargar la textura
	glGenTextures(1, &textureTerrainGID); // Creando el id de la textura del landingpad
	glBindTexture(GL_TEXTURE_2D, textureTerrainGID); // Se enlaza la textura
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Wrapping en el eje u
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Wrapping en el eje v
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Filtering de minimización
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Filtering de maximimizacion
	if(textureG.getData()){
		// Transferir los datos de la imagen a la tarjeta
		glTexImage2D(GL_TEXTURE_2D, 0, textureG.getChannels() == 3 ? GL_RGB : GL_RGBA, textureG.getWidth(), textureG.getHeight(), 0,
		textureG.getChannels() == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, textureG.getData());
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else 
		std::cout << "Fallo la carga de textura" << std::endl;
	textureG.freeImage(); // Liberamos memoria

	// Definiendo la textura
	Texture textureB("../Elementos_proyecto/Textures/path.png");
	textureB.loadImage(); // Cargar la textura
	glGenTextures(1, &textureTerrainBID); // Creando el id de la textura del landingpad
	glBindTexture(GL_TEXTURE_2D, textureTerrainBID); // Se enlaza la textura
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Wrapping en el eje u
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Wrapping en el eje v
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Filtering de minimización
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Filtering de maximimizacion
	if(textureB.getData()){
		// Transferir los datos de la imagen a la tarjeta
		glTexImage2D(GL_TEXTURE_2D, 0, textureB.getChannels() == 3 ? GL_RGB : GL_RGBA, textureB.getWidth(), textureB.getHeight(), 0,
		textureB.getChannels() == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, textureB.getData());
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else 
		std::cout << "Fallo la carga de textura" << std::endl;
	textureB.freeImage(); // Liberamos memoria

	// Definiendo la textura
	Texture textureBlendMap("../Elementos_proyecto/Textures/blendMap_black.png");
	textureBlendMap.loadImage(); // Cargar la textura
	glGenTextures(1, &textureTerrainBlendMapID); // Creando el id de la textura del landingpad
	glBindTexture(GL_TEXTURE_2D, textureTerrainBlendMapID); // Se enlaza la textura
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Wrapping en el eje u
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Wrapping en el eje v
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Filtering de minimización
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Filtering de maximimizacion
	if(textureBlendMap.getData()){
		// Transferir los datos de la imagen a la tarjeta
		glTexImage2D(GL_TEXTURE_2D, 0, textureBlendMap.getChannels() == 3 ? GL_RGB : GL_RGBA, textureBlendMap.getWidth(), textureBlendMap.getHeight(), 0,
		textureBlendMap.getChannels() == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, textureBlendMap.getData());
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else 
		std::cout << "Fallo la carga de textura" << std::endl;
	textureBlendMap.freeImage(); // Liberamos memoria

	// Definiendo la textura
	Texture textureIntro1("../Elementos_proyecto/Pantalla/Intro1.png");
	textureIntro1.loadImage(); // Cargar la textura
	glGenTextures(1, &textureInit1ID); // Creando el id de la textura del landingpad
	glBindTexture(GL_TEXTURE_2D, textureInit1ID); // Se enlaza la textura
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Wrapping en el eje u
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Wrapping en el eje v
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Filtering de minimización
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Filtering de maximimizacion
	if(textureIntro1.getData()){
		// Transferir los datos de la imagen a la tarjeta
		glTexImage2D(GL_TEXTURE_2D, 0, textureIntro1.getChannels() == 3 ? GL_RGB : GL_RGBA, textureIntro1.getWidth(), textureIntro1.getHeight(), 0,
		textureIntro1.getChannels() == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, textureIntro1.getData());
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else 
		std::cout << "Fallo la carga de textura" << std::endl;
	textureIntro1.freeImage(); // Liberamos memoria

	// Definiendo la textura
	Texture textureIntro2("../Elementos_proyecto/Pantalla/Intro2.png");
	textureIntro2.loadImage(); // Cargar la textura
	glGenTextures(1, &textureInit2ID); // Creando el id de la textura del landingpad
	glBindTexture(GL_TEXTURE_2D, textureInit2ID); // Se enlaza la textura
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Wrapping en el eje u
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Wrapping en el eje v
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Filtering de minimización
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Filtering de maximimizacion
	if(textureIntro2.getData()){
		// Transferir los datos de la imagen a la tarjeta
		glTexImage2D(GL_TEXTURE_2D, 0, textureIntro2.getChannels() == 3 ? GL_RGB : GL_RGBA, textureIntro2.getWidth(), textureIntro2.getHeight(), 0,
		textureIntro2.getChannels() == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, textureIntro2.getData());
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else 
		std::cout << "Fallo la carga de textura" << std::endl;
	textureIntro2.freeImage(); // Liberamos memoria
	

	// Definiendo la textura
	Texture textureScreen("../Elementos_proyecto/Pantalla/LifeFull.png");
	textureScreen.loadImage(); // Cargar la textura
	glGenTextures(1, &textureScreenID); // Creando el id de la textura del landingpad
	glBindTexture(GL_TEXTURE_2D, textureScreenID); // Se enlaza la textura
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Wrapping en el eje u
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Wrapping en el eje v
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Filtering de minimización
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Filtering de maximimizacion
	if(textureScreen.getData()){
		// Transferir los datos de la imagen a la tarjeta
		glTexImage2D(GL_TEXTURE_2D, 0, textureScreen.getChannels() == 3 ? GL_RGB : GL_RGBA, textureScreen.getWidth(), textureScreen.getHeight(), 0,
		textureScreen.getChannels() == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, textureScreen.getData());
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else 
		std::cout << "Fallo la carga de textura" << std::endl;
	textureScreen.freeImage(); // Liberamos memoria

	// Definiendo la textura
	Texture textureScreen3("../Elementos_proyecto/Pantalla/Life3.png");
	textureScreen3.loadImage(); // Cargar la textura
	glGenTextures(1, &textureScreen3ID); // Creando el id de la textura del landingpad
	glBindTexture(GL_TEXTURE_2D, textureScreen3ID); // Se enlaza la textura
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Wrapping en el eje u
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Wrapping en el eje v
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Filtering de minimización
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Filtering de maximimizacion
	if(textureScreen3.getData()){
		// Transferir los datos de la imagen a la tarjeta
		glTexImage2D(GL_TEXTURE_2D, 0, textureScreen3.getChannels() == 3 ? GL_RGB : GL_RGBA, textureScreen3.getWidth(), textureScreen3.getHeight(), 0,
		textureScreen3.getChannels() == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, textureScreen3.getData());
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else 
		std::cout << "Fallo la carga de textura" << std::endl;
	textureScreen3.freeImage(); // Liberamos memoria

	// Definiendo la textura
	Texture textureScreen2("../Elementos_proyecto/Pantalla/Life2.png");
	textureScreen2.loadImage(); // Cargar la textura
	glGenTextures(1, &textureScreen2ID); // Creando el id de la textura del landingpad
	glBindTexture(GL_TEXTURE_2D, textureScreen2ID); // Se enlaza la textura
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Wrapping en el eje u
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Wrapping en el eje v
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Filtering de minimización
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Filtering de maximimizacion
	if(textureScreen2.getData()){
		// Transferir los datos de la imagen a la tarjeta
		glTexImage2D(GL_TEXTURE_2D, 0, textureScreen2.getChannels() == 3 ? GL_RGB : GL_RGBA, textureScreen2.getWidth(), textureScreen2.getHeight(), 0,
		textureScreen2.getChannels() == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, textureScreen2.getData());
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else 
		std::cout << "Fallo la carga de textura" << std::endl;
	textureScreen2.freeImage(); // Liberamos memoria

	// Definiendo la textura
	Texture textureScreen1("../Elementos_proyecto/Pantalla/Life1.png");
	textureScreen1.loadImage(); // Cargar la textura
	glGenTextures(1, &textureScreen1ID); // Creando el id de la textura del landingpad
	glBindTexture(GL_TEXTURE_2D, textureScreen1ID); // Se enlaza la textura
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Wrapping en el eje u
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Wrapping en el eje v
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Filtering de minimización
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Filtering de maximimizacion
	if(textureScreen1.getData()){
		// Transferir los datos de la imagen a la tarjeta
		glTexImage2D(GL_TEXTURE_2D, 0, textureScreen1.getChannels() == 3 ? GL_RGB : GL_RGBA, textureScreen1.getWidth(), textureScreen1.getHeight(), 0,
		textureScreen1.getChannels() == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, textureScreen1.getData());
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else 
		std::cout << "Fallo la carga de textura" << std::endl;
	textureScreen1.freeImage(); // Liberamos memoria

	// Definiendo la textura GAME OVER
	Texture textureScreenGO("../Elementos_proyecto/Pantalla/GameOver.png");
	textureScreenGO.loadImage(); // Cargar la textura
	glGenTextures(1, &textureScreenGOID); // Creando el id de la textura del landingpad
	glBindTexture(GL_TEXTURE_2D, textureScreenGOID); // Se enlaza la textura
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Wrapping en el eje u
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Wrapping en el eje v
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Filtering de minimización
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Filtering de maximimizacion
	if(textureScreenGO.getData()){
		// Transferir los datos de la imagen a la tarjeta
		glTexImage2D(GL_TEXTURE_2D, 0, textureScreenGO.getChannels() == 3 ? GL_RGB : GL_RGBA, textureScreenGO.getWidth(), textureScreenGO.getHeight(), 0,
		textureScreenGO.getChannels() == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, textureScreenGO.getData());
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else 
		std::cout << "Fallo la carga de textura" << std::endl;
	textureScreenGO.freeImage(); // Liberamos memoria

	// Definiendo la textura GAME OVER
	Texture textureScreenWN("../Elementos_proyecto/Pantalla/Win.png");
	textureScreenWN.loadImage(); // Cargar la textura
	glGenTextures(1, &textureScreenWNID); // Creando el id de la textura del landingpad
	glBindTexture(GL_TEXTURE_2D, textureScreenWNID); // Se enlaza la textura
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Wrapping en el eje u
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Wrapping en el eje v
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Filtering de minimización
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Filtering de maximimizacion
	if(textureScreenWN.getData()){
		// Transferir los datos de la imagen a la tarjeta
		glTexImage2D(GL_TEXTURE_2D, 0, textureScreenWN.getChannels() == 3 ? GL_RGB : GL_RGBA, textureScreenWN.getWidth(), textureScreenWN.getHeight(), 0,
		textureScreenWN.getChannels() == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, textureScreenWN.getData());
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else 
		std::cout << "Fallo la carga de textura" << std::endl;
	textureScreenWN.freeImage(); // Liberamos memoria


	/*******************************************
	 * OpenAL init
	 *******************************************/
	alutInit(0, nullptr);
	alListenerfv(AL_POSITION, listenerPos);
	alListenerfv(AL_VELOCITY, listenerVel);
	alListenerfv(AL_ORIENTATION, listenerOri);
	alGetError(); // clear any error messages
	if (alGetError() != AL_NO_ERROR) {
		printf("- Error creating buffers !!\n");
		exit(1);
	}
	else {
		printf("init() - No errors yet.");
	}
	// Generate buffers, or else no sound will happen!
	alGenBuffers(NUM_BUFFERS, buffer);
	buffer[0] = alutCreateBufferFromFile("../Elementos_proyecto/sound/music.wav");
	buffer[1] = alutCreateBufferFromFile("../Elementos_proyecto/sound/music.wav");
	buffer[2] = alutCreateBufferFromFile("../Elementos_proyecto/sound/music.wav");
	buffer[3] = alutCreateBufferFromFile("../Elementos_proyecto/sound/music.wav");
	buffer[4] = alutCreateBufferFromFile("../Elementos_proyecto/sound/music.wav");
	buffer[5] = alutCreateBufferFromFile("../Elementos_proyecto/sound/music.wav");
	int errorAlut = alutGetError();
	if (errorAlut != ALUT_ERROR_NO_ERROR){
		printf("- Error open files with alut %d !!\n", errorAlut);
		exit(2);
	}

	alGetError(); /* clear error */
	alGenSources(NUM_SOURCES, source);

	if (alGetError() != AL_NO_ERROR) {
		printf("- Error creating sources !!\n");
		exit(2);
	}
	else {
		printf("init - no errors after alGenSources\n");
	}
	//On al GAIN last parameter is VOLUME

	float volumenAudios= 3.5f;
	alSourcef(source[0], AL_PITCH, 1.0f);
	alSourcef(source[0], AL_GAIN, volumenAudios);
	alSourcefv(source[0], AL_POSITION, source0Pos);
	alSourcefv(source[0], AL_VELOCITY, source0Vel);
	alSourcei(source[0], AL_BUFFER, buffer[0]);
	alSourcei(source[0], AL_LOOPING, AL_TRUE);
	alSourcef(source[0], AL_MAX_DISTANCE, 1000);

	alSourcef(source[1], AL_PITCH, 1.0f);
	alSourcef(source[1], AL_GAIN, volumenAudios);
	alSourcefv(source[1], AL_POSITION, source1Pos);
	alSourcefv(source[1], AL_VELOCITY, source1Vel);
	alSourcei(source[1], AL_BUFFER, buffer[1]);
	alSourcei(source[1], AL_LOOPING, AL_TRUE);
	alSourcef(source[1], AL_MAX_DISTANCE, 1000);

	alSourcef(source[2], AL_PITCH, 1.0f);
	alSourcef(source[2], AL_GAIN, volumenAudios);
	alSourcefv(source[2], AL_POSITION, source2Pos);
	alSourcefv(source[2], AL_VELOCITY, source2Vel);
	alSourcei(source[2], AL_BUFFER, buffer[2]);
	alSourcei(source[2], AL_LOOPING, AL_TRUE);
	alSourcef(source[2], AL_MAX_DISTANCE, 1000);
	//
	alSourcef(source[3], AL_PITCH, 1.0f);
	alSourcef(source[3], AL_GAIN, volumenAudios);
	alSourcefv(source[3], AL_POSITION, source3Pos);
	alSourcefv(source[3], AL_VELOCITY, source3Vel);
	alSourcei(source[3], AL_BUFFER, buffer[3]);
	alSourcei(source[3], AL_LOOPING, AL_TRUE);
	alSourcef(source[3], AL_MAX_DISTANCE, 1000);

	alSourcef(source[4], AL_PITCH, 1.0f);
	alSourcef(source[4], AL_GAIN, volumenAudios);
	alSourcefv(source[4], AL_POSITION, source4Pos);
	alSourcefv(source[4], AL_VELOCITY, source4Vel);
	alSourcei(source[4], AL_BUFFER, buffer[4]);
	alSourcei(source[4], AL_LOOPING, AL_TRUE);
	alSourcef(source[4], AL_MAX_DISTANCE, 1000);

	alSourcef(source[5], AL_PITCH, 1.0f);
	alSourcef(source[5], AL_GAIN, volumenAudios);
	alSourcefv(source[5], AL_POSITION, source5Pos);
	alSourcefv(source[5], AL_VELOCITY, source5Vel);
	alSourcei(source[5], AL_BUFFER, buffer[5]);
	alSourcei(source[5], AL_LOOPING, AL_TRUE);
	alSourcef(source[5], AL_MAX_DISTANCE, 1000);

	/*******************************************
	 * Inicializacion del framebuffer para
	 * almacenar el buffer de profunidadad
	 *******************************************/
	glGenFramebuffers(1, &depthMapFBO);
	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
				 SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void destroy() {
	glfwDestroyWindow(window);
	glfwTerminate();
	// --------- IMPORTANTE ----------
	// Eliminar los shader y buffers creados.

	// Shaders Delete
	shader.destroy();
	shaderMulLighting.destroy();
	shaderSkybox.destroy();
	shaderTerrain.destroy();
	/*shaderParticlesFountain.destroy();*/

	// Basic objects Delete
	boxCesped.destroy();
	modelTiendas1.destroy();
	modelTiendas2.destroy();
	modelBasura.destroy();
	modelPared.destroy();
	modelTecho.destroy();
	modelMuebles.destroy();
	modelTelevision1.destroy();
	modelTelevision2.destroy();
	modelTelevision3.destroy();
	modelTiendasSalida.destroy();

	// Custom objects Delete
	mayowModelAnimate.destroy();
	spiderModelAnimate.destroy();

	// Terrains objects Delete
	terrain.destroy();

	// Textures Delete
	glBindTexture(GL_TEXTURE_2D, 0);
	glDeleteTextures(1, &textureCespedID);
	glDeleteTextures(1, &textureTerrainBID);
	glDeleteTextures(1, &textureTerrainGID);
	glDeleteTextures(1, &textureTerrainRID);
	glDeleteTextures(1, &textureTerrainBlendMapID);
	glDeleteTextures(1, &textureInit1ID);
	glDeleteTextures(1, &textureInit2ID);
	glDeleteTextures(1, &textureScreenID);
	glDeleteTextures(1, &textureParticleFountainID);

	// Cube Maps Delete
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	glDeleteTextures(1, &skyboxTextureID);
}

void reshapeCallback(GLFWwindow *Window, int widthRes, int heightRes) {
	screenWidth = widthRes;
	screenHeight = heightRes;
	glViewport(0, 0, widthRes, heightRes);
}

void keyCallback(GLFWwindow *window, int key, int scancode, int action,
		int mode) {
	if (action == GLFW_PRESS) {
		switch (key) {
		case GLFW_KEY_ESCAPE:
			exitApp = true;
			break;
		}
	}
}

void mouseCallback(GLFWwindow *window, double xpos, double ypos) {
	offsetX = xpos - lastMousePosX;
	offsetY = ypos - lastMousePosY;
	lastMousePosX = xpos;
	lastMousePosY = ypos;
}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset){
	if( distanceFromTarget > 2 && yoffset > 0)
		distanceFromTarget -= yoffset;
	else if (distanceFromTarget >= 2 && distanceFromTarget < 10 && yoffset <= 0)
		distanceFromTarget -= yoffset;
	camera->setDistanceFromTarget(distanceFromTarget);
}

void mouseButtonCallback(GLFWwindow *window, int button, int state, int mod) {
	if (state == GLFW_PRESS) {
		switch (button) {
		case GLFW_MOUSE_BUTTON_RIGHT:
			std::cout << "lastMousePos.y:" << lastMousePosY << std::endl;
			break;
		case GLFW_MOUSE_BUTTON_LEFT:
			std::cout << "lastMousePos.x:" << lastMousePosX << std::endl;
			break;
		case GLFW_MOUSE_BUTTON_MIDDLE:
			std::cout << "lastMousePos.x:" << lastMousePosX << std::endl;
			std::cout << "lastMousePos.y:" << lastMousePosY << std::endl;
			break;
		}
	}
}

bool processInput(bool continueApplication) {
	if (exitApp || glfwWindowShouldClose(window) != 0) {
		return false;
	}
//AQUI PARA IMAGENES EN PANTALLA
	if(!iniciaPartida){
		bool presionarEnter = glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS;
		if(textureActivaID == textureInit1ID && presionarEnter){
			iniciaPartida = true;
			textureActivaID = textureScreenID;

			
		}
		else if(!presionarOpcion && glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS){
			presionarOpcion = true;
			if(textureActivaID == textureInit1ID)
				textureActivaID = textureInit2ID;
			else if(textureActivaID == textureInit2ID)
				textureActivaID = textureInit1ID;
		}
		else if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_RELEASE)
			presionarOpcion = false;
	}
	if(iniciaPartida){
		if(playerLife  == 4){
			textureActivaID = textureScreenID;
		}
		if(playerLife  == 3){
			textureActivaID = textureScreen3ID;
		}
		if(playerLife  == 2){
			textureActivaID = textureScreen2ID;
		}
		if(playerLife  == 1){
			textureActivaID = textureScreen1ID;
		}
		if(playerLife  == 0){
			textureActivaID = textureScreenGOID;
			psi = false;
		}
		if(playerLife  == -1){
			textureActivaID = textureScreenWNID;
			psi = false;
		}
	}


	if (glfwJoystickPresent(GLFW_JOYSTICK_1) == GL_TRUE) {
		std::cout << "Esta presente el joystick" << std::endl;
		int axesCount, buttonCount;
		const float * axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axesCount);
		std::cout << "Número de ejes disponibles :=>" << axesCount << std::endl;
		std::cout << "Left Stick X axis: " << axes[0] << std::endl;
		std::cout << "Left Stick Y axis: " << axes[1] << std::endl;
		std::cout << "Left Trigger/L2: " << axes[2] << std::endl;
		std::cout << "Right Stick X axis: " << axes[3] << std::endl;
		std::cout << "Right Stick Y axis: " << axes[4] << std::endl;
		std::cout << "Right Trigger/R2: " << axes[5] << std::endl;

		if(fabs(axes[1]) > 0.2){
			modelMatrixMayow = glm::translate(modelMatrixMayow, glm::vec3(0, 0, -axes[1] * 0.1));
			animationMayowIndex = 2;
		}if(fabs(axes[0]) > 0.2){
			modelMatrixMayow = glm::rotate(modelMatrixMayow, glm::radians(-axes[0] * 0.5f), glm::vec3(0, 1, 0));
			animationMayowIndex = 2;
		}

		if(fabs(axes[3]) > 0.2){
			camera->mouseMoveCamera(axes[3], 0.0, deltaTime);
		}if(fabs(axes[4]) > 0.2){
			camera->mouseMoveCamera(0.0, axes[4], deltaTime);
		}

		const unsigned char * buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonCount);
		std::cout << "Número de botones disponibles :=>" << buttonCount << std::endl;
		if(buttons[0] == GLFW_PRESS)
			std::cout << "Se presiona x" << std::endl;

		if(!isJump && buttons[0] == GLFW_PRESS){
			isJump = true;
			startTimeJump = currTime;
			tmv = 0;
		}
	}

	if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
		camera->mouseMoveCamera(offsetX, 0.0, deltaTime);
		camera->mouseMoveCamera(0.0, offsetY, deltaTime);
	}
		
	if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
		camera->mouseMoveCamera(0.0, offsetY, deltaTime);

	offsetX = 0;
	offsetY = 0;

	//Control musica temporal
	//ABOUT SOUNDS
	if(glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS){
		playing = false;
	}
	if(glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS){
		playing = true;
	}

	// Controles de main
	if (modelSelected == 0 && glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
		modelMatrixMayow = glm::rotate(modelMatrixMayow, 0.02f, glm::vec3(0, 1, 0));
		animationMayowIndex = 2;
	} else if (modelSelected == 0 && glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
		modelMatrixMayow = glm::rotate(modelMatrixMayow, -0.02f, glm::vec3(0, 1, 0));
		animationMayowIndex = 2;
	}
	if (modelSelected == 0 && glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
		modelMatrixMayow = glm::translate(modelMatrixMayow, glm::vec3(0.0, 0.0, 0.055));
		animationMayowIndex = 2;
	}
	else if (modelSelected == 0 && glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
		modelMatrixMayow = glm::translate(modelMatrixMayow, glm::vec3(0.0, 0.0, -0.055));
		animationMayowIndex = 2;
	}

	bool keySpaceStatus = glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS;
	if(!isJump && keySpaceStatus){
		isJump = true;
		startTimeJump = currTime;
		tmv = 0;
	}

	glfwPollEvents();
	return continueApplication;
}

void prepareScene(){

	terrain.setShader(&shaderTerrain);
	
	//Segmento corto de las tiendas
	modelTiendas1.setShader(&shaderMulLighting);

	//Segmento largo de las tiendas
	modelTiendas2.setShader(&shaderMulLighting);

	//Botes de basura
	modelBasura.setShader(&shaderMulLighting);

	modelPared.setShader(&shaderMulLighting);
	modelTecho.setShader(&shaderMulLighting);
	modelMuebles.setShader(&shaderMulLighting);
	modelTelevision1.setShader(&shaderMulLighting);
	modelTelevision2.setShader(&shaderMulLighting);
	modelTelevision3.setShader(&shaderMulLighting);

	modelTiendasSalida.setShader(&shaderMulLighting);

	//Main
	mayowModelAnimate.setShader(&shaderMulLighting);
	spiderModelAnimate.setShader(&shaderMulLighting);

}

void prepareDepthScene(){

	terrain.setShader(&shaderDepth);

	//Segmento corto de las tiendas
	modelTiendas1.setShader(&shaderDepth);

	//Segmento largo de las tiendas
	modelTiendas2.setShader(&shaderDepth);

	//Basura
	modelBasura.setShader(&shaderDepth);
	modelPared.setShader(&shaderDepth);
	modelTecho.setShader(&shaderDepth);
	modelMuebles.setShader(&shaderDepth);
	modelTelevision1.setShader(&shaderDepth);
	modelTelevision2.setShader(&shaderDepth);
	modelTelevision3.setShader(&shaderDepth);

	modelTiendasSalida.setShader(&shaderDepth);

	//Main
	mayowModelAnimate.setShader(&shaderDepth);
	spiderModelAnimate.setShader(&shaderDepth);

}

void renderSolidScene(){
	/*******************************************
	 * Terrain Cesped
	 *******************************************/
	// Se activa la textura del agua
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureCespedID);
	shaderTerrain.setInt("backgroundTexture", 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, textureTerrainRID);
	shaderTerrain.setInt("rTexture", 1);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, textureTerrainGID);
	shaderTerrain.setInt("gTexture", 2);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, textureTerrainBID);
	shaderTerrain.setInt("bTexture", 3);
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, textureTerrainBlendMapID);
	shaderTerrain.setInt("blendMapTexture", 4);
	shaderTerrain.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(80, 80)));
	terrain.setPosition(glm::vec3(100, 0, 100));
	terrain.render();
	shaderTerrain.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(0, 0)));
	glBindTexture(GL_TEXTURE_2D, 0);

	/*******************************************
	 * Custom objects obj
	 *******************************************/
	// Forze to enable the unit texture to 0 always ----------------- IMPORTANT
	//Render de tiendas
	//matrixModelTiendas1[3][1] = terrain.getHeightTerrain(matrixModelTiendas1[3][0], matrixModelTiendas1[3][2]);
	modelTiendas1.render(matrixModelTiendas1);
	modelTiendas1.render(matrixModelTiendas1Ext);
	modelTiendas2.render(matrixModelTiendas2);
	modelTiendas2.render(matrixModelTiendas2Ext);
	modelBasura.render(matrixModelBasura);
	modelTecho.render(matrixModelTecho);
	modelPared.render(matrixModelPared);
	modelTelevision1.render(matrixModelTelevision1);
	modelTelevision2.render(matrixModelTelevision2);
	modelTelevision3.render(matrixModelTelevision3);
	modelTelevision1.render(matrixModelTelevision1Ext);
	modelTelevision2.render(matrixModelTelevision2Ext);
	modelTelevision3.render(matrixModelTelevision3Ext);
	modelTiendasSalida.render(matrixModelTiendasSalida);

	//Renderizacion de sillas y mesas cortas 
	modelMuebles.render(matrixModelMuebles);
	modelMuebles.render(matrixModelMuebles2);
	modelMuebles.render(matrixModelMuebles3);
	modelMuebles.render(matrixModelMuebles4);
	modelMuebles.render(matrixModelMuebles5);
	modelMuebles.render(matrixModelMuebles6);
	modelMuebles.render(matrixModelMuebles7);
	modelMuebles.render(matrixModelMuebles8);
	modelMuebles.render(matrixModelMuebles9);
	modelMuebles.render(matrixModelMuebles10);
	modelMuebles.render(matrixModelMuebles11);
	modelMuebles.render(matrixModelMuebles12);
	modelMuebles.render(matrixModelMuebles13);
	modelMuebles.render(matrixModelMuebles14);
	modelMuebles.render(matrixModelMuebles15);
	modelMuebles.render(matrixModelMuebles16);
	
	modelMuebles.render(matrixModelMuebles17);
	modelMuebles.render(matrixModelMuebles18);
	modelMuebles.render(matrixModelMuebles19);
	modelMuebles.render(matrixModelMuebles20);
	modelMuebles.render(matrixModelMuebles21);
	modelMuebles.render(matrixModelMuebles22);
	modelMuebles.render(matrixModelMuebles23);
	modelMuebles.render(matrixModelMuebles24);
	
	modelMuebles.render(matrixModelMuebles25);
	modelMuebles.render(matrixModelMuebles26);
	modelMuebles.render(matrixModelMuebles27);
	modelMuebles.render(matrixModelMuebles28);
	modelMuebles.render(matrixModelMuebles29);
	modelMuebles.render(matrixModelMuebles30);
	modelMuebles.render(matrixModelMuebles31);
	modelMuebles.render(matrixModelMuebles32);
	
	modelMuebles.render(matrixModelMuebles33);
	modelMuebles.render(matrixModelMuebles34);
	modelMuebles.render(matrixModelMuebles35);
	modelMuebles.render(matrixModelMuebles36);

//Cover
	modelMuebles.render(matrixModelMueblesExt1);
	modelMuebles.render(matrixModelMueblesExt2);
	modelMuebles.render(matrixModelMueblesExt3);
	modelMuebles.render(matrixModelMueblesExt4);
	modelMuebles.render(matrixModelMueblesExt5);
	modelMuebles.render(matrixModelMueblesExt6);
	modelMuebles.render(matrixModelMueblesExt7);
	modelMuebles.render(matrixModelMueblesExt8);

	glActiveTexture(GL_TEXTURE0);



	/*****************************************
	 * Objetos animados por huesos
	 * **************************************/
	glm::vec3 ejey = glm::normalize(terrain.getNormalTerrain(modelMatrixMayow[3][0], modelMatrixMayow[3][2]));
	glm::vec3 ejex = glm::vec3(modelMatrixMayow[0]);
	glm::vec3 ejez = glm::normalize(glm::cross(ejex, ejey));
	ejex = glm::normalize(glm::cross(ejey, ejez));
	modelMatrixMayow[0] = glm::vec4(ejex, 0.0);
	modelMatrixMayow[1] = glm::vec4(ejey, 0.0);
	modelMatrixMayow[2] = glm::vec4(ejez, 0.0);
	modelMatrixMayow[3][1] = -GRAVITY * tmv * tmv + 3.5 * tmv + terrain.getHeightTerrain(modelMatrixMayow[3][0], modelMatrixMayow[3][2]);
	tmv = currTime - startTimeJump;
	if(modelMatrixMayow[3][1] < terrain.getHeightTerrain(modelMatrixMayow[3][0], modelMatrixMayow[3][2])){
		isJump = false;
		modelMatrixMayow[3][1] = terrain.getHeightTerrain(modelMatrixMayow[3][0], modelMatrixMayow[3][2]);
	}
	glm::mat4 modelMatrixMayowBody = glm::mat4(modelMatrixMayow);
	
	//modelMatrixMayowBody = glm::scale(modelMatrixMayowBody, glm::vec3(MCScale));
	modelMatrixMayowBody = glm::scale(modelMatrixMayowBody, glm::vec3(0.0012f));
	mayowModelAnimate.setAnimationIndex(animationMayowIndex);
	mayowModelAnimate.render(modelMatrixMayowBody);
	//animationMayowIndex = 1;

	//ARAÑA
	modelMatrixSpider[3][1] = terrain.getHeightTerrain(modelMatrixSpider[3][0], modelMatrixSpider[3][2]);
	glm::mat4 modelMatrixSpiderBody = glm::mat4(modelMatrixSpider);
	spiderModelAnimate.setAnimationIndex(animationSpiderIndex);
	spiderModelAnimate.render(modelMatrixSpider);

	//ARAÑA 2
	modelMatrixSpider2[3][1] = terrain.getHeightTerrain(modelMatrixSpider2[3][0], modelMatrixSpider2[3][2]);
	glm::mat4 modelMatrixSpider2Body = glm::mat4(modelMatrixSpider2);
	spiderModelAnimate.setAnimationIndex(animationSpiderIndex2);
	spiderModelAnimate.render(modelMatrixSpider2);

	//ARAÑA 3
	modelMatrixSpider3[3][1] = terrain.getHeightTerrain(modelMatrixSpider3[3][0], modelMatrixSpider3[3][2]);
	glm::mat4 modelMatrixSpider3Body = glm::mat4(modelMatrixSpider3);
	spiderModelAnimate.setAnimationIndex(animationSpiderIndex3);
	spiderModelAnimate.render(modelMatrixSpider3);

	//ARAÑA 4
	modelMatrixSpider4[3][1] = terrain.getHeightTerrain(modelMatrixSpider4[3][0], modelMatrixSpider4[3][2]);
	glm::mat4 modelMatrixSpider4Body = glm::mat4(modelMatrixSpider4);
	spiderModelAnimate.setAnimationIndex(animationSpiderIndex4);
	spiderModelAnimate.render(modelMatrixSpider4);

	//ARAÑA 5
	modelMatrixSpider5[3][1] = terrain.getHeightTerrain(modelMatrixSpider5[3][0], modelMatrixSpider5[3][2]);
	glm::mat4 modelMatrixSpider5Body = glm::mat4(modelMatrixSpider5);
	spiderModelAnimate.setAnimationIndex(animationSpiderIndex5);
	spiderModelAnimate.render(modelMatrixSpider5);


	/*******************************************
	 * Skybox
	 *******************************************/
	GLint oldCullFaceMode;
	GLint oldDepthFuncMode;
	// deshabilita el modo del recorte de caras ocultas para ver las esfera desde adentro
	glGetIntegerv(GL_CULL_FACE_MODE, &oldCullFaceMode);
	glGetIntegerv(GL_DEPTH_FUNC, &oldDepthFuncMode);
	shaderSkybox.setFloat("skybox", 0);
	glCullFace(GL_FRONT);
	glDepthFunc(GL_LEQUAL);
	glActiveTexture(GL_TEXTURE0);
	skyboxSphere.render();
	glCullFace(oldCullFaceMode);
	glDepthFunc(oldDepthFuncMode);
}

void renderAlphaScene(bool render = true){
	/**********
	 * Update the position with alpha objects
	 */
	// Update the aircraft
	blendingUnsorted.find("aircraft")->second = glm::vec3(modelMatrixAircraft[3]);
	// Update the lambo
	blendingUnsorted.find("lambo")->second = glm::vec3(modelMatrixLambo[3]);
	// Update the helicopter
	blendingUnsorted.find("heli")->second = glm::vec3(modelMatrixHeli[3]);

	/**********
	 * Sorter with alpha objects
	 */
	std::map<float, std::pair<std::string, glm::vec3>> blendingSorted;
	std::map<std::string, glm::vec3>::iterator itblend;
	for(itblend = blendingUnsorted.begin(); itblend != blendingUnsorted.end(); itblend++){
		float distanceFromView = glm::length(camera->getPosition() - itblend->second);
		blendingSorted[distanceFromView] = std::make_pair(itblend->first, itblend->second);
	}

	/**********
	 * Render de las transparencias
	 */

	if(render){
		/************Render de imagen de frente**************/
		shaderTexture.setMatrix4("projection", 1, false, glm::value_ptr(glm::mat4(1.0)));
		shaderTexture.setMatrix4("view", 1, false, glm::value_ptr(glm::mat4(1.0)));
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureActivaID);
		shaderTexture.setInt("outTexture", 0);
		glEnable(GL_BLEND);
		boxIntro.render();
		glDisable(GL_BLEND);

		modelText->render(textoNoticia, -1, 0);
	}
}

void renderScene(){
	renderSolidScene();
	renderAlphaScene(false);
}

void applicationLoop() {
	

	glm::vec3 axis;
	glm::vec3 target;
	float angleTarget;
				

	//Matrices de tiendas (1) corto, (2) largo
	matrixModelTiendas1 = glm::translate(matrixModelTiendas1, glm::vec3(23.0f, 2.0f, -5.0f));
	matrixModelTiendas1 = glm::rotate(matrixModelTiendas1, glm::radians(-90.0f), glm::vec3(1,0,0));

	matrixModelTiendas2 = glm::translate(matrixModelTiendas2, glm::vec3(-1.0f, 2.0f, -7.2f));
	matrixModelTiendas2 = glm::rotate(matrixModelTiendas2, glm::radians(-90.0f), glm::vec3(1,0,0));
	matrixModelTiendas2 = glm::rotate(matrixModelTiendas2, glm::radians(90.0f), glm::vec3(0,0,1));

	matrixModelTiendas2Ext = glm::translate(matrixModelTiendas2Ext, glm::vec3(-58.0f, 2.0f, 40.2f));
	matrixModelTiendas2Ext = glm::rotate(matrixModelTiendas2Ext, glm::radians(-90.0f), glm::vec3(1,0,0));
	matrixModelTiendas2Ext = glm::rotate(matrixModelTiendas2Ext, glm::radians(-90.0f), glm::vec3(0,0,1));

	matrixModelTiendas1Ext = glm::translate(matrixModelTiendas1Ext, glm::vec3(-84.0f, 2.0f, 38.10f));
	matrixModelTiendas1Ext = glm::rotate(matrixModelTiendas1Ext, glm::radians(-90.0f), glm::vec3(1,0,0));
	matrixModelTiendas1Ext = glm::rotate(matrixModelTiendas1Ext, glm::radians(180.0f), glm::vec3(0,0,1));
	//

	//Puerta
	matrixModelTiendasSalida = glm::translate(matrixModelTiendasSalida, glm::vec3(-82.0f, 1.0f, 40.0f));
	matrixModelTiendasSalida = glm::rotate(matrixModelTiendasSalida, glm::radians(-90.0f), glm::vec3(1,0,0));
	matrixModelTiendasSalida = glm::rotate(matrixModelTiendasSalida, glm::radians(90.0f), glm::vec3(0,0,1));
	matrixModelTiendasSalida= glm::scale(matrixModelTiendasSalida, glm::vec3(0.00129f));

	//Basura
	matrixModelBasura = glm::translate(matrixModelBasura, glm::vec3(5.0f, 1.7f, 7.2f));
	matrixModelBasura = glm::rotate(matrixModelBasura, glm::radians(-90.0f), glm::vec3(1,0,0));
	matrixModelBasura = glm::scale(matrixModelBasura, glm::vec3(0.01f, 0.5f, 0.5f));

	//Muebles

	/*********MESAS Y SILLAS CHICAS******
	
	*************************************/
	matrixModelMuebles = glm::translate(matrixModelMuebles, glm::vec3(1.0f, 0.99f, 11.0f));
	matrixModelMuebles = glm::scale(matrixModelMuebles, glm::vec3(0.012f));

	matrixModelMuebles2 = glm::translate(matrixModelMuebles2, glm::vec3(-7.70f, 0.99f, 9.0f));
	matrixModelMuebles2 = glm::scale(matrixModelMuebles2, glm::vec3(0.012f));

	matrixModelMuebles3 = glm::translate(matrixModelMuebles3, glm::vec3(-23.2f, 0.99f, 12.0f));
	matrixModelMuebles3 = glm::scale(matrixModelMuebles3, glm::vec3(0.012f));

	matrixModelMuebles4 = glm::translate(matrixModelMuebles4, glm::vec3(-38.10f, 0.99f, 10.0f));
	matrixModelMuebles4 = glm::scale(matrixModelMuebles4, glm::vec3(0.012f));

	matrixModelMuebles5 = glm::translate(matrixModelMuebles5, glm::vec3(-46.3f, 0.99f, 8.0f));
	matrixModelMuebles5 = glm::scale(matrixModelMuebles5, glm::vec3(0.012f));

	matrixModelMuebles6 = glm::translate(matrixModelMuebles6, glm::vec3(-51.4f, 0.99f, 12.0f));
	matrixModelMuebles6 = glm::scale(matrixModelMuebles6, glm::vec3(0.012f));

	matrixModelMuebles7 = glm::translate(matrixModelMuebles7, glm::vec3(-58.2f, 0.99f, 9.0f));
	matrixModelMuebles7 = glm::scale(matrixModelMuebles7, glm::vec3(0.012f));

	matrixModelMuebles8 = glm::translate(matrixModelMuebles8, glm::vec3(-68.50f, 0.99f, 10.0f));
	matrixModelMuebles8 = glm::scale(matrixModelMuebles8, glm::vec3(0.012f));

// *************************************rep al lado 2
	matrixModelMuebles9 = glm::translate(matrixModelMuebles9, glm::vec3(0.6f, 0.99f, 21.0f));
	matrixModelMuebles9 = glm::scale(matrixModelMuebles9, glm::vec3(0.012f));

	matrixModelMuebles10 = glm::translate(matrixModelMuebles10, glm::vec3(-8.10f, 0.99f, 22.0f));
	matrixModelMuebles10 = glm::scale(matrixModelMuebles10, glm::vec3(0.012f));

	matrixModelMuebles11 = glm::translate(matrixModelMuebles11, glm::vec3(-25.7f, 0.99f, 24.0f));
	matrixModelMuebles11 = glm::scale(matrixModelMuebles11, glm::vec3(0.012f));

	matrixModelMuebles12 = glm::translate(matrixModelMuebles12, glm::vec3(-33.50f, 0.99f, 19.0f));
	matrixModelMuebles12 = glm::scale(matrixModelMuebles12, glm::vec3(0.012f));

	matrixModelMuebles13 = glm::translate(matrixModelMuebles13, glm::vec3(-42.3f, 0.99f, 18.0f));
	matrixModelMuebles13 = glm::scale(matrixModelMuebles13, glm::vec3(0.012f));

	matrixModelMuebles14 = glm::translate(matrixModelMuebles14, glm::vec3(-50.4f, 0.99f, 20.0f));
	matrixModelMuebles14 = glm::scale(matrixModelMuebles14, glm::vec3(0.012f));

	matrixModelMuebles15 = glm::translate(matrixModelMuebles15, glm::vec3(-59.9f, 0.99f, 21.0f));
	matrixModelMuebles15 = glm::scale(matrixModelMuebles15, glm::vec3(0.012f));

	matrixModelMuebles16 = glm::translate(matrixModelMuebles16, glm::vec3(-67.10f, 0.99f, 22.0f));
	matrixModelMuebles16 = glm::scale(matrixModelMuebles16, glm::vec3(0.012f));
	
	//*****************************************Rep al lado 3

	matrixModelMuebles17 = glm::translate(matrixModelMuebles17, glm::vec3(1.0f, 0.99f, 31.0f));
	matrixModelMuebles17 = glm::scale(matrixModelMuebles17, glm::vec3(0.012f));

	matrixModelMuebles18 = glm::translate(matrixModelMuebles18, glm::vec3(-9.30f, 0.99f, 31.0f));
	matrixModelMuebles18 = glm::scale(matrixModelMuebles18, glm::vec3(0.012f));

	matrixModelMuebles19 = glm::translate(matrixModelMuebles19, glm::vec3(-27.50f, 0.99f, 30.0f));
	matrixModelMuebles19 = glm::scale(matrixModelMuebles19, glm::vec3(0.012f));

	matrixModelMuebles20 = glm::translate(matrixModelMuebles20, glm::vec3(-32.70f, 0.99f, 32.0f));
	matrixModelMuebles20 = glm::scale(matrixModelMuebles20, glm::vec3(0.012f));

	matrixModelMuebles21 = glm::translate(matrixModelMuebles21, glm::vec3(-41.8f, 0.99f, 29.0f));
	matrixModelMuebles21 = glm::scale(matrixModelMuebles21, glm::vec3(0.012f));

	matrixModelMuebles22 = glm::translate(matrixModelMuebles22, glm::vec3(-52.2f, 0.99f, 28.0f));
	matrixModelMuebles22 = glm::scale(matrixModelMuebles22, glm::vec3(0.012f));

	matrixModelMuebles23 = glm::translate(matrixModelMuebles23, glm::vec3(-60.5f, 0.99f, 31.0f));
	matrixModelMuebles23 = glm::scale(matrixModelMuebles23, glm::vec3(0.012f));

	matrixModelMuebles24 = glm::translate(matrixModelMuebles24, glm::vec3(-65.90f, 0.99f, 32.0f));
	matrixModelMuebles24 = glm::scale(matrixModelMuebles24, glm::vec3(0.012f));

	//***************************************Rep al lado 0

	matrixModelMuebles25 = glm::translate(matrixModelMuebles25, glm::vec3(-1.3f, 0.99f, 1.2f));
	matrixModelMuebles25 = glm::scale(matrixModelMuebles25, glm::vec3(0.012f));

	matrixModelMuebles26 = glm::translate(matrixModelMuebles26, glm::vec3(-7.70f, 0.99f, 2.2f));
	matrixModelMuebles26 = glm::scale(matrixModelMuebles26, glm::vec3(0.012f));

	matrixModelMuebles27 = glm::translate(matrixModelMuebles27, glm::vec3(-26.80f, 0.99f, 0.2f));
	matrixModelMuebles27 = glm::scale(matrixModelMuebles27, glm::vec3(0.012f));

	matrixModelMuebles28 = glm::translate(matrixModelMuebles28, glm::vec3(-34.20f, 0.99f, 1.2f));
	matrixModelMuebles28 = glm::scale(matrixModelMuebles28, glm::vec3(0.012f));

	matrixModelMuebles29 = glm::translate(matrixModelMuebles29, glm::vec3(-45.30f, 0.99f, 1.2f));
	matrixModelMuebles29 = glm::scale(matrixModelMuebles29, glm::vec3(0.012f));

	matrixModelMuebles30 = glm::translate(matrixModelMuebles30, glm::vec3(-49.15f, 0.99f, 3.2f));
	matrixModelMuebles30 = glm::scale(matrixModelMuebles30, glm::vec3(0.012f));

	matrixModelMuebles31 = glm::translate(matrixModelMuebles31, glm::vec3(-57.80f, 0.99f, -1.2f));
	matrixModelMuebles31 = glm::scale(matrixModelMuebles31, glm::vec3(0.012f));

	matrixModelMuebles32 = glm::translate(matrixModelMuebles32, glm::vec3(-69.250f, 0.99f, 0.2f));
	matrixModelMuebles32 = glm::scale(matrixModelMuebles32, glm::vec3(0.012f));

	//****************************Rep al lado 4


	matrixModelMuebles37 = glm::translate(matrixModelMuebles37, glm::vec3(1.50f, 0.99f, -11.2f));
	matrixModelMuebles37 = glm::scale(matrixModelMuebles37, glm::vec3(0.012f));

	matrixModelMuebles38 = glm::translate(matrixModelMuebles38, glm::vec3(-9.750f, 0.99f, -12.2f));
	matrixModelMuebles38 = glm::scale(matrixModelMuebles38, glm::vec3(0.012f));

	matrixModelMuebles39 = glm::translate(matrixModelMuebles39, glm::vec3(-24.10f, 0.99f, -12.2f));
	matrixModelMuebles39 = glm::scale(matrixModelMuebles39, glm::vec3(0.012f));

	matrixModelMuebles40 = glm::translate(matrixModelMuebles40, glm::vec3(-36.950f, 0.99f, -10.2f));
	matrixModelMuebles40 = glm::scale(matrixModelMuebles40, glm::vec3(0.012f));

	matrixModelMuebles41 = glm::translate(matrixModelMuebles41, glm::vec3(-45.30f, 0.99f, -13.2f));
	matrixModelMuebles41 = glm::scale(matrixModelMuebles41, glm::vec3(0.012f));

	matrixModelMuebles42 = glm::translate(matrixModelMuebles42, glm::vec3(-51.45f, 0.99f, -13.2f));
	matrixModelMuebles42 = glm::scale(matrixModelMuebles42, glm::vec3(0.012f));

	matrixModelMuebles43 = glm::translate(matrixModelMuebles43, glm::vec3(-60.20f, 0.99f, -11.2f));
	matrixModelMuebles43 = glm::scale(matrixModelMuebles43, glm::vec3(0.012f));

	matrixModelMuebles44 = glm::translate(matrixModelMuebles44, glm::vec3(-68.850f, 0.99f, -10.2f));
	matrixModelMuebles44 = glm::scale(matrixModelMuebles44, glm::vec3(0.012f));

	//x=76
	matrixModelMuebles45 = glm::translate(matrixModelMuebles45, glm::vec3(-78.70f, 0.99f, -11.2f));
	matrixModelMuebles45 = glm::scale(matrixModelMuebles45, glm::vec3(0.012f));

//Cover line for x=-17 & x=8 & x=76
//x=8
	matrixModelMueblesExt1 = glm::translate(matrixModelMueblesExt1, glm::vec3(8.90f, 0.99f, 1.0f));
	matrixModelMueblesExt1 = glm::scale(matrixModelMueblesExt1, glm::vec3(0.012f));
	matrixModelMueblesExt2 = glm::translate(matrixModelMueblesExt2, glm::vec3(8.60, 0.99f, 6.2f));
	matrixModelMueblesExt2 = glm::scale(matrixModelMueblesExt2, glm::vec3(0.012f));
	matrixModelMueblesExt3 = glm::translate(matrixModelMueblesExt3, glm::vec3(8.50f, 0.99f, 21.0f));
	matrixModelMueblesExt3 = glm::scale(matrixModelMueblesExt3, glm::vec3(0.012f));
	matrixModelMueblesExt4 = glm::translate(matrixModelMueblesExt4, glm::vec3(8.50f, 0.99f, 29.0f));
	matrixModelMueblesExt4 = glm::scale(matrixModelMueblesExt4, glm::vec3(0.012f));

//x=-17
	matrixModelMueblesExt5 = glm::translate(matrixModelMueblesExt5, glm::vec3(-17.20f, 0.99f, -1.0f));
	matrixModelMueblesExt5 = glm::scale(matrixModelMueblesExt5, glm::vec3(0.012f));
	matrixModelMueblesExt6 = glm::translate(matrixModelMueblesExt6, glm::vec3(-16.40, 0.99f, 8.2f));
	matrixModelMueblesExt6 = glm::scale(matrixModelMueblesExt6, glm::vec3(0.012f));
	matrixModelMueblesExt7 = glm::translate(matrixModelMueblesExt7, glm::vec3(-18.80f, 0.99f, 19.0f));
	matrixModelMueblesExt7 = glm::scale(matrixModelMueblesExt7, glm::vec3(0.012f));
	matrixModelMueblesExt8 = glm::translate(matrixModelMueblesExt8, glm::vec3(-17.70f, 0.99f, 32.0f));
	matrixModelMueblesExt8 = glm::scale(matrixModelMueblesExt8, glm::vec3(0.012f));

	//x=76

	matrixModelMuebles33 = glm::translate(matrixModelMuebles33, glm::vec3(-76.90f, 0.99f, 0.0f));
	matrixModelMuebles33 = glm::scale(matrixModelMuebles33, glm::vec3(0.012f));
	matrixModelMuebles34 = glm::translate(matrixModelMuebles34, glm::vec3(-76.60, 0.99f, 7.2f));
	matrixModelMuebles34 = glm::scale(matrixModelMuebles34, glm::vec3(0.012f));
	matrixModelMuebles35 = glm::translate(matrixModelMuebles35, glm::vec3(-76.50f, 0.99f, 20.0f));
	matrixModelMuebles35 = glm::scale(matrixModelMuebles35, glm::vec3(0.012f));
	matrixModelMuebles36 = glm::translate(matrixModelMuebles36, glm::vec3(-76.70f, 0.99f, 30.0f));
	matrixModelMuebles36 = glm::scale(matrixModelMuebles36, glm::vec3(0.012f));


/***********************FIN DE SILLAS CORTAS ******************************/

	//Televisiones
	//pared normal
	matrixModelTelevision1 = glm::translate(matrixModelTelevision1, glm::vec3(8.0f, 5.99f, -6.2f));
	matrixModelTelevision1 = glm::rotate(matrixModelTelevision1, glm::radians(-90.0f), glm::vec3(1,0,0));
	//matrixModelTelevision1 = glm::scale(matrixModelTelevision1, glm::vec3(0.5f));

	//pared opuesta
	matrixModelTelevision2 = glm::translate(matrixModelTelevision2, glm::vec3(-8.5f, 5.99f, 39.1f));
	matrixModelTelevision2 = glm::rotate(matrixModelTelevision2, glm::radians(-90.0f), glm::vec3(1,0,0));
	matrixModelTelevision2 = glm::rotate(matrixModelTelevision2, glm::radians(180.0f), glm::vec3(0,0,1));
	//matrixModelTelevision2 = glm::scale(matrixModelTelevision2, glm::vec3(0.5f));

	//pared normal
	matrixModelTelevision3 = glm::translate(matrixModelTelevision3, glm::vec3(-25.0f, 5.99f, -6.2f));
	matrixModelTelevision3 = glm::rotate(matrixModelTelevision3, glm::radians(-90.0f), glm::vec3(1,0,0));
	//matrixModelTelevision3 = glm::scale(matrixModelTelevision3, glm::vec3(0.5f));

//Repeticion de las televisiones:
	//Televisiones
	//pared opuesta
	matrixModelTelevision1Ext = glm::translate(matrixModelTelevision1Ext, glm::vec3(-41.5f, 5.99f, 39.1f));
	matrixModelTelevision1Ext = glm::rotate(matrixModelTelevision1Ext, glm::radians(-90.0f), glm::vec3(1,0,0));
	matrixModelTelevision1Ext = glm::rotate(matrixModelTelevision1Ext, glm::radians(180.0f), glm::vec3(0,0,1));
	//matrixModelTelevision1Ext = glm::scale(matrixModelTelevision1Ext, glm::vec3(0.5f));

	//pared normal
	matrixModelTelevision2Ext = glm::translate(matrixModelTelevision2Ext, glm::vec3(-58.0f, 5.99f, -6.2f));
	matrixModelTelevision2Ext = glm::rotate(matrixModelTelevision2Ext, glm::radians(-90.0f), glm::vec3(1,0,0));
	//matrixModelTelevision2Ext = glm::rotate(matrixModelTelevision2Ext, glm::radians(180.0f), glm::vec3(0,0,1));
	//matrixModelTelevision2 = glm::scale(matrixModelTelevision2, glm::vec3(0.5f));s

	//pared opuesta
	matrixModelTelevision3Ext = glm::translate(matrixModelTelevision3Ext, glm::vec3(-74.5f, 5.99f, 39.1f));
	matrixModelTelevision3Ext = glm::rotate(matrixModelTelevision3Ext, glm::radians(-90.0f), glm::vec3(1,0,0));
	matrixModelTelevision3Ext = glm::rotate(matrixModelTelevision3Ext, glm::radians(180.0f), glm::vec3(0,0,1));
	//matrixModelTelevision3 = glm::scale(matrixModelTelevision3, glm::vec3(0.5f));

	//Paredes y techo
	matrixModelPared = glm::translate(matrixModelPared, glm::vec3(-120.0f, 2.0f, 17.0f));
	matrixModelPared = glm::rotate(matrixModelPared, glm::radians(-180.0f), glm::vec3(1,0,0));
	matrixModelPared = glm::rotate(matrixModelPared, glm::radians(-90.0f), glm::vec3(0,1,0));
	matrixModelPared = glm::scale(matrixModelPared, glm::vec3(25.0f,10.0f,7.0f));
	

	matrixModelTecho = glm::translate(matrixModelTecho, glm::vec3(-30.0f, 10.0f, 15.0f));
	matrixModelTecho = glm::rotate(matrixModelTecho, glm::radians(90.0f), glm::vec3(1,0,0));
	matrixModelTecho = glm::scale(matrixModelTecho, glm::vec3(60.0f,25.0f,45.0f));

	//Personaje principal
	modelMatrixMayow = glm::translate(modelMatrixMayow, glm::vec3(13.0f, 0.05f, -5.0f));
	modelMatrixMayow = glm::rotate(modelMatrixMayow, glm::radians(-90.0f), glm::vec3(0, 1, 0));

	//Enemigo 1 ARAÑA
	modelMatrixSpider = glm::translate(modelMatrixSpider, glm::vec3(5.0f, 2.5f, 30.1f));
	modelMatrixSpider = glm::scale(modelMatrixSpider, glm:: vec3(0.010f));

	//con z se pone de cabeza
	
	//Enemigo 2 ARAÑA
	modelMatrixSpider2 = glm::translate(modelMatrixSpider2, glm::vec3(-55.5f, 2.5f, 30.1f));
	modelMatrixSpider2 = glm::scale(modelMatrixSpider2, glm:: vec3(0.010f));
	

	//Enemigo 3 ARAÑA
	modelMatrixSpider3 = glm::translate(modelMatrixSpider3, glm::vec3(9.0f, 2.5f, 35.1f));
	modelMatrixSpider3 = glm::rotate(modelMatrixSpider3, glm::radians(90.0f), glm::vec3(0, 1, 0));
	modelMatrixSpider3 = glm::scale(modelMatrixSpider3, glm:: vec3(0.010f));

	//Enemigo 4 ARAÑA
	modelMatrixSpider4 = glm::translate(modelMatrixSpider4, glm::vec3(-80.90f, 2.5f, 30.0f));
	modelMatrixSpider4 = glm::scale(modelMatrixSpider4, glm:: vec3(0.010f));

	//Enemigo 5 ARAÑA
	modelMatrixSpider5 = glm::translate(modelMatrixSpider5, glm::vec3(-62.20f, 2.5f, -3.2f));
	modelMatrixSpider5 = glm::scale(modelMatrixSpider5, glm:: vec3(0.010f));
	
	lastTime = TimeManager::Instance().GetTime();

	textureActivaID = textureInit1ID;

	glm::vec3 lightPos = glm::vec3(10.0, 10.0, -10.0);

	shadowBox = new ShadowBox(-lightPos, camera.get(), 15.0f, 0.1f, 45.0f);

	while (psi) {
		currTime = TimeManager::Instance().GetTime();
		if(currTime - lastTime < 0.016666667){
			glfwPollEvents();
			continue;
		}
		lastTime = currTime;
		TimeManager::Instance().CalculateFrameRate(true);
		deltaTime = TimeManager::Instance().DeltaTime;
		psi = processInput(true);

		std::map<std::string, bool> collisionDetection;


		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float) screenWidth / (float) screenHeight, 0.01f, 100.0f);

		
		axis = glm::axis(glm::quat_cast(modelMatrixMayow));
		angleTarget = glm::angle(glm::quat_cast(modelMatrixMayow));
		target = modelMatrixMayow[3];
		
		if(std::isnan(angleTarget))
			angleTarget = 0.0;
		if(axis.y < 0)
			angleTarget = -angleTarget;
		if(modelSelected == 1)
			angleTarget -= glm::radians(90.0f);
		camera->setCameraTarget(target);
		camera->setAngleTarget(angleTarget);
		camera->updateCamera();
		glm::mat4 view = camera->getViewMatrix();

		shadowBox->update(screenWidth, screenHeight);
		glm::vec3 centerBox = shadowBox->getCenter();

		// Projection light shadow mapping
		glm::mat4 lightProjection = glm::mat4(1.0f), lightView = glm::mat4(1.0f);
		glm::mat4 lightSpaceMatrix;
		lightProjection[0][0] = 2.0f / shadowBox->getWidth();
		lightProjection[1][1] = 2.0f / shadowBox->getHeight();
		lightProjection[2][2] = -2.0f / shadowBox->getLength();
		lightProjection[3][3] = 1.0f;
		lightView = glm::lookAt(centerBox, centerBox + glm::normalize(-lightPos), glm::vec3(0.0, 1.0, 0.0));
		lightSpaceMatrix = lightProjection * lightView;
		shaderDepth.setMatrix4("lightSpaceMatrix", 1, false, glm::value_ptr(lightSpaceMatrix));

		// Settea la matriz de vista y projection al shader con solo color
		shader.setMatrix4("projection", 1, false, glm::value_ptr(projection));
		shader.setMatrix4("view", 1, false, glm::value_ptr(view));

		// Settea la matriz de vista y projection al shader con skybox
		shaderSkybox.setMatrix4("projection", 1, false,
				glm::value_ptr(projection));
		shaderSkybox.setMatrix4("view", 1, false,
				glm::value_ptr(glm::mat4(glm::mat3(view))));
		// Settea la matriz de vista y projection al shader con multiples luces
		shaderMulLighting.setMatrix4("projection", 1, false,
					glm::value_ptr(projection));
		shaderMulLighting.setMatrix4("view", 1, false,
				glm::value_ptr(view));
		shaderMulLighting.setMatrix4("lightSpaceMatrix", 1, false,
				glm::value_ptr(lightSpaceMatrix));
		// Settea la matriz de vista y projection al shader con multiples luces
		shaderTerrain.setMatrix4("projection", 1, false,
				glm::value_ptr(projection));
		shaderTerrain.setMatrix4("view", 1, false,
				glm::value_ptr(view));
		shaderTerrain.setMatrix4("lightSpaceMatrix", 1, false,
				glm::value_ptr(lightSpaceMatrix));


		/*******************************************
		 * Propiedades de neblina
		 *******************************************/
		shaderMulLighting.setVectorFloat3("fogColor", glm::value_ptr(glm::vec3(0.3, 0.3, 0.3)));
		shaderTerrain.setVectorFloat3("fogColor", glm::value_ptr(glm::vec3(0.3, 0.3, 0.3)));
		shaderSkybox.setVectorFloat3("fogColor", glm::value_ptr(glm::vec3(0.08, 0.08, 0.08)));

		/*******************************************
		 * Propiedades Luz direccional
		 *******************************************/
		shaderMulLighting.setVectorFloat3("viewPos", glm::value_ptr(camera->getPosition()));
		shaderMulLighting.setVectorFloat3("directionalLight.light.ambient", glm::value_ptr(glm::vec3(0.002, 0.002, 0.002)));
		shaderMulLighting.setVectorFloat3("directionalLight.light.diffuse", glm::value_ptr(glm::vec3(0.005, 0.005, 0.005)));
		shaderMulLighting.setVectorFloat3("directionalLight.light.specular", glm::value_ptr(glm::vec3(0.002, 0.002, 0.002)));
		shaderMulLighting.setVectorFloat3("directionalLight.direction", glm::value_ptr(glm::vec3(-0.707106781, -0.707106781, 0.0)));

		shaderTerrain.setVectorFloat3("viewPos", glm::value_ptr(camera->getPosition()));
		shaderTerrain.setVectorFloat3("directionalLight.light.ambient", glm::value_ptr(glm::vec3(0.002, 0.002, 0.002)));
		shaderTerrain.setVectorFloat3("directionalLight.light.diffuse", glm::value_ptr(glm::vec3(0.005, 0.005, 0.005)));
		shaderTerrain.setVectorFloat3("directionalLight.light.specular", glm::value_ptr(glm::vec3(0.002, 0.002, 0.002)));
		shaderTerrain.setVectorFloat3("directionalLight.direction", glm::value_ptr(glm::vec3(-0.707106781, -0.707106781, 0.0)));
		/*******************************************
		 * Propiedades SpotLights
		 *******************************************/
		shaderMulLighting.setInt("spotLightCount", 1);
		shaderTerrain.setInt("spotLightCount", 1);
		glm::vec3 spotPosition = glm::vec3(modelMatrixHeli * glm::vec4(0.0, 0.2, 1.75, 1.0));
		shaderMulLighting.setVectorFloat3("spotLights[0].light.ambient", glm::value_ptr(glm::vec3(0.0, 0.0, 0.0)));
		shaderMulLighting.setVectorFloat3("spotLights[0].light.diffuse", glm::value_ptr(glm::vec3(0.002, 0.003, 0.002)));
		shaderMulLighting.setVectorFloat3("spotLights[0].light.specular", glm::value_ptr(glm::vec3(0.003, 0.003, 0.003)));
		shaderMulLighting.setVectorFloat3("spotLights[0].position", glm::value_ptr(spotPosition));
		shaderMulLighting.setVectorFloat3("spotLights[0].direction", glm::value_ptr(glm::vec3(0, -1, 0)));
		shaderMulLighting.setFloat("spotLights[0].constant", 1.0);
		shaderMulLighting.setFloat("spotLights[0].linear", 0.07);
		shaderMulLighting.setFloat("spotLights[0].quadratic", 0.03);
		shaderMulLighting.setFloat("spotLights[0].cutOff", cos(glm::radians(12.5f)));
		shaderMulLighting.setFloat("spotLights[0].outerCutOff", cos(glm::radians(15.0f)));
		shaderTerrain.setVectorFloat3("spotLights[0].light.ambient", glm::value_ptr(glm::vec3(0.0, 0.0, 0.0)));
		shaderTerrain.setVectorFloat3("spotLights[0].light.diffuse", glm::value_ptr(glm::vec3(0.002, 0.003, 0.002)));
		shaderTerrain.setVectorFloat3("spotLights[0].light.specular", glm::value_ptr(glm::vec3(0.003, 0.003, 0.003)));
		shaderTerrain.setVectorFloat3("spotLights[0].position", glm::value_ptr(spotPosition));
		shaderTerrain.setVectorFloat3("spotLights[0].direction", glm::value_ptr(glm::vec3(0, -1, 0)));
		shaderTerrain.setFloat("spotLights[0].constant", 1.0);
		shaderTerrain.setFloat("spotLights[0].linear", 0.07);
		shaderTerrain.setFloat("spotLights[0].quadratic", 0.03);
		shaderTerrain.setFloat("spotLights[0].cutOff", cos(glm::radians(12.5f)));
		shaderTerrain.setFloat("spotLights[0].outerCutOff", cos(glm::radians(15.0f)));

		/*******************************************
		 * Propiedades PointLights
		 *******************************************/
		shaderMulLighting.setInt("pointLightCount", lamp1Position.size() + lamp2Position.size());
		shaderTerrain.setInt("pointLightCount", lamp1Position.size() + lamp2Position.size());
		for(int i = 0; i < lamp1Position.size(); i++){
			glm::mat4 matrixAdjustLamp = glm::mat4(1.0);
			matrixAdjustLamp = glm::translate(matrixAdjustLamp, lamp1Position[i]);
			matrixAdjustLamp = glm::rotate(matrixAdjustLamp, glm::radians(lamp1Orientation[i]), glm::vec3(0, 1, 0));
			matrixAdjustLamp = glm::scale(matrixAdjustLamp, glm::vec3(0.5));
			matrixAdjustLamp = glm::translate(matrixAdjustLamp, glm::vec3(0.0, 5.99, 0));
			glm::vec3 lampPosition = glm::vec3(matrixAdjustLamp[3]);
			shaderMulLighting.setVectorFloat3("pointLights[" + std::to_string(i) + "].light.ambient", glm::value_ptr(glm::vec3(0.4, 0.4, 0.4)));
			shaderMulLighting.setVectorFloat3("pointLights[" + std::to_string(i) + "].light.diffuse", glm::value_ptr(glm::vec3(0.4, 0.4, 0.4)));
			shaderMulLighting.setVectorFloat3("pointLights[" + std::to_string(i) + "].light.specular", glm::value_ptr(glm::vec3(0.6, 0.6, 0.6)));
			shaderMulLighting.setVectorFloat3("pointLights[" + std::to_string(i) + "].position", glm::value_ptr(lampPosition));
			shaderMulLighting.setFloat("pointLights[" + std::to_string(i) + "].constant", 1.0);
			shaderMulLighting.setFloat("pointLights[" + std::to_string(i) + "].linear", 0.09);
			shaderMulLighting.setFloat("pointLights[" + std::to_string(i) + "].quadratic", 0.02);
			shaderTerrain.setVectorFloat3("pointLights[" + std::to_string(i) + "].light.ambient", glm::value_ptr(glm::vec3(0.4, 0.4, 0.4)));
			shaderTerrain.setVectorFloat3("pointLights[" + std::to_string(i) + "].light.diffuse", glm::value_ptr(glm::vec3(0.4, 0.4, 0.4)));
			shaderTerrain.setVectorFloat3("pointLights[" + std::to_string(i) + "].light.specular", glm::value_ptr(glm::vec3(0.6, 0.6, 0.6)));
			shaderTerrain.setVectorFloat3("pointLights[" + std::to_string(i) + "].position", glm::value_ptr(lampPosition));
			shaderTerrain.setFloat("pointLights[" + std::to_string(i) + "].constant", 1.0);
			shaderTerrain.setFloat("pointLights[" + std::to_string(i) + "].linear", 0.09);
			shaderTerrain.setFloat("pointLights[" + std::to_string(i) + "].quadratic", 0.02);
		}
		
		
		for(int i = 0; i < lamp2Position.size(); i++){
			glm::mat4 matrixAdjustLamp = glm::mat4(1.0);
			matrixAdjustLamp = glm::translate(matrixAdjustLamp, lamp2Position[i]);
			matrixAdjustLamp = glm::rotate(matrixAdjustLamp, glm::radians(lamp2Orientation[i]), glm::vec3(0, 1, 0));
			matrixAdjustLamp = glm::scale(matrixAdjustLamp, glm::vec3(1.0));
			matrixAdjustLamp = glm::translate(matrixAdjustLamp, glm::vec3(0.75, 5.0, 0));
			glm::vec3 lampPosition = glm::vec3(matrixAdjustLamp[3]);
			shaderMulLighting.setVectorFloat3("pointLights[" + std::to_string(lamp1Position.size() + i) + "].light.ambient", glm::value_ptr(glm::vec3(0.002, 0.0016, 0.0001)));
			shaderMulLighting.setVectorFloat3("pointLights[" + std::to_string(lamp1Position.size() + i) + "].light.diffuse", glm::value_ptr(glm::vec3(0.004, 0.0032, 0.0002)));
			shaderMulLighting.setVectorFloat3("pointLights[" + std::to_string(lamp1Position.size() + i) + "].light.specular", glm::value_ptr(glm::vec3(0.006, 0.0058, 0.0003)));
			shaderMulLighting.setVectorFloat3("pointLights[" + std::to_string(lamp1Position.size() + i) + "].position", glm::value_ptr(lampPosition));
			shaderMulLighting.setFloat("pointLights[" + std::to_string(lamp1Position.size() + i) + "].constant", 1.0);
			shaderMulLighting.setFloat("pointLights[" + std::to_string(lamp1Position.size() + i) + "].linear", 0.09);
			shaderMulLighting.setFloat("pointLights[" + std::to_string(lamp1Position.size() + i) + "].quadratic", 0.02);
			shaderTerrain.setVectorFloat3("pointLights[" + std::to_string(lamp1Position.size() + i) + "].light.ambient", glm::value_ptr(glm::vec3(0.002, 0.0016, 0.0001)));
			shaderTerrain.setVectorFloat3("pointLights[" + std::to_string(lamp1Position.size() + i) + "].light.diffuse", glm::value_ptr(glm::vec3(0.004, 0.0032, 0.0002)));
			shaderTerrain.setVectorFloat3("pointLights[" + std::to_string(lamp1Position.size() + i) + "].light.specular", glm::value_ptr(glm::vec3(0.006, 0.0058, 0.0003)));
			shaderTerrain.setVectorFloat3("pointLights[" + std::to_string(lamp1Position.size() + i) + "].position", glm::value_ptr(lampPosition));
			shaderTerrain.setFloat("pointLights[" + std::to_string(lamp1Position.size() + i) + "].constant", 1.0);
			shaderTerrain.setFloat("pointLights[" + std::to_string(lamp1Position.size() + i) + "].linear", 0.09);
			shaderTerrain.setFloat("pointLights[" + std::to_string(lamp1Position.size() + i) + "].quadratic", 0.02);
		}

		/************Render de imagen de frente**************/
		if(!iniciaPartida){
			shaderTexture.setMatrix4("projection", 1, false, glm::value_ptr(glm::mat4(1.0)));
			shaderTexture.setMatrix4("view", 1, false, glm::value_ptr(glm::mat4(1.0)));
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, textureActivaID);
			shaderTexture.setInt("outTexture", 0);
			boxIntro.render();
			glfwSwapBuffers(window);
			continue;
		}

		/*******************************************
		 * 1.- We render the depth buffer
		 *******************************************/
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// render scene from light's point of view
		glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
		glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
		glClear(GL_DEPTH_BUFFER_BIT);
		glCullFace(GL_FRONT);
		prepareDepthScene();
		renderScene();
		glCullFace(GL_BACK);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		/*******************************************
		 * Render the normal objects
		 *******************************************/
		glViewport(0, 0, screenWidth, screenHeight);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		prepareScene();
		glActiveTexture(GL_TEXTURE10);
		glBindTexture(GL_TEXTURE_2D, depthMap);
		shaderMulLighting.setInt("shadowMap", 10);
		shaderTerrain.setInt("shadowMap", 10);
		renderSolidScene();

		/*******************************************
		 * Creacion de colliders
		 * IMPORTANT do this before interpolations
		 *******************************************/

		// Collider de mayow

		AbstractModel::OBB mayowCollider;
		glm::mat4 modelmatrixColliderMayow = glm::mat4(modelMatrixMayow);
		modelmatrixColliderMayow = glm::rotate(modelmatrixColliderMayow,
				glm::radians(-90.0f), glm::vec3(1, 0, 0));
		// Set the orientation of collider before doing the scale
		mayowCollider.u = glm::quat_cast(modelmatrixColliderMayow);
		//MCSCALE HERE WAS USED, BUT ITS JUST THE SAME VALUES
		modelmatrixColliderMayow = glm::scale(modelmatrixColliderMayow, glm::vec3(0.1f));
		modelmatrixColliderMayow = glm::translate(modelmatrixColliderMayow,
				glm::vec3(mayowModelAnimate.getObb().c.x,
						mayowModelAnimate.getObb().c.y,
						mayowModelAnimate.getObb().c.z));
						//QUI TAMBIEN SE USO MCSCALE
		mayowCollider.e = mayowModelAnimate.getObb().e * glm::vec3(0.1f) * glm::vec3(0.787401574, 0.787401574, 0.787401574);
		mayowCollider.c = glm::vec3(modelmatrixColliderMayow[3]);
		addOrUpdateColliders(collidersOBB, "mayow", mayowCollider, modelMatrixMayow);


		// Collider de ARAÑA
		AbstractModel::OBB SpiderCollider;
		glm::mat4 modelmatrixColliderSpider = glm::mat4(modelMatrixSpider);
		modelmatrixColliderSpider = glm::rotate(modelmatrixColliderSpider,
				glm::radians(-90.0f), glm::vec3(1, 0, 0));
		// Set the orientation of collider before doing the scale
		SpiderCollider.u = glm::quat_cast(modelmatrixColliderSpider);
		//MCSCALE HERE WAS USED, BUT ITS JUST THE SAME VALUES
		modelmatrixColliderSpider = glm::scale(modelmatrixColliderSpider, glm::vec3(0.1f));
		modelmatrixColliderSpider = glm::translate(modelmatrixColliderSpider,
				glm::vec3(spiderModelAnimate.getObb().c.x,
						spiderModelAnimate.getObb().c.y,
						spiderModelAnimate.getObb().c.z));
						//QUI TAMBIEN SE USO MCSCALE
		SpiderCollider.e = spiderModelAnimate.getObb().e * glm::vec3(0.1f) * glm::vec3(0.787401574, 0.787401574, 0.787401574);
		SpiderCollider.c = glm::vec3(modelmatrixColliderSpider[3]);
		addOrUpdateColliders(collidersOBB, "Spider", SpiderCollider, modelMatrixSpider);

		// Collider de ARAÑA 2
		AbstractModel::OBB Spider2Collider;
		glm::mat4 modelmatrixColliderSpider2 = glm::mat4(modelMatrixSpider2);
		modelmatrixColliderSpider2 = glm::rotate(modelmatrixColliderSpider2,
				glm::radians(-90.0f), glm::vec3(1, 0, 0));
		// Set the orientation of collider before doing the scale
		Spider2Collider.u = glm::quat_cast(modelmatrixColliderSpider2);
		//MCSCALE HERE WAS USED, BUT ITS JUST THE SAME VALUES
		modelmatrixColliderSpider2 = glm::scale(modelmatrixColliderSpider2, glm::vec3(0.1f));
		modelmatrixColliderSpider2 = glm::translate(modelmatrixColliderSpider2,
				glm::vec3(spiderModelAnimate.getObb().c.x,
						spiderModelAnimate.getObb().c.y,
						spiderModelAnimate.getObb().c.z));
						//QUI TAMBIEN SE USO MCSCALE
		Spider2Collider.e = spiderModelAnimate.getObb().e * glm::vec3(0.1f) * glm::vec3(0.787401574, 0.787401574, 0.787401574);
		Spider2Collider.c = glm::vec3(modelmatrixColliderSpider2[3]);
		addOrUpdateColliders(collidersOBB, "Spider2", Spider2Collider, modelMatrixSpider2);

		// Collider de ARAÑA 3
		AbstractModel::OBB Spider3Collider;
		glm::mat4 modelmatrixColliderSpider3 = glm::mat4(modelMatrixSpider3);
		modelmatrixColliderSpider3 = glm::rotate(modelmatrixColliderSpider3,
				glm::radians(-90.0f), glm::vec3(1, 0, 0));
		// Set the orientation of collider before doing the scale
		Spider3Collider.u = glm::quat_cast(modelmatrixColliderSpider3);
		//MCSCALE HERE WAS USED, BUT ITS JUST THE SAME VALUES
		modelmatrixColliderSpider3 = glm::scale(modelmatrixColliderSpider3, glm::vec3(0.1f));
		modelmatrixColliderSpider3 = glm::translate(modelmatrixColliderSpider3,
				glm::vec3(spiderModelAnimate.getObb().c.x,
						spiderModelAnimate.getObb().c.y,
						spiderModelAnimate.getObb().c.z));
						//QUI TAMBIEN SE USO MCSCALE
		Spider3Collider.e = spiderModelAnimate.getObb().e * glm::vec3(0.1f) * glm::vec3(0.787401574, 0.787401574, 0.787401574);
		Spider3Collider.c = glm::vec3(modelmatrixColliderSpider3[3]);
		addOrUpdateColliders(collidersOBB, "Spider3", Spider3Collider, modelMatrixSpider3);
		
		// Collider de ARAÑA 4
		AbstractModel::OBB Spider4Collider;
		glm::mat4 modelmatrixColliderSpider4 = glm::mat4(modelMatrixSpider4);
		modelmatrixColliderSpider4 = glm::rotate(modelmatrixColliderSpider4,
				glm::radians(-90.0f), glm::vec3(1, 0, 0));
		// Set the orientation of collider before doing the scale
		Spider4Collider.u = glm::quat_cast(modelmatrixColliderSpider4);
		//MCSCALE HERE WAS USED, BUT ITS JUST THE SAME VALUES
		modelmatrixColliderSpider4 = glm::scale(modelmatrixColliderSpider4, glm::vec3(0.1f));
		modelmatrixColliderSpider4 = glm::translate(modelmatrixColliderSpider4,
				glm::vec3(spiderModelAnimate.getObb().c.x,
						spiderModelAnimate.getObb().c.y,
						spiderModelAnimate.getObb().c.z));
						//QUI TAMBIEN SE USO MCSCALE
		Spider4Collider.e = spiderModelAnimate.getObb().e * glm::vec3(0.1f) * glm::vec3(0.787401574, 0.787401574, 0.787401574);
		Spider4Collider.c = glm::vec3(modelmatrixColliderSpider4[3]);
		addOrUpdateColliders(collidersOBB, "Spider4", Spider4Collider, modelMatrixSpider4);

		// Collider de ARAÑA 5
		AbstractModel::OBB Spider5Collider;
		glm::mat4 modelmatrixColliderSpider5 = glm::mat4(modelMatrixSpider5);
		modelmatrixColliderSpider5 = glm::rotate(modelmatrixColliderSpider5,
				glm::radians(-90.0f), glm::vec3(1, 0, 0));
		// Set the orientation of collider before doing the scale
		Spider5Collider.u = glm::quat_cast(modelmatrixColliderSpider5);
		//MCSCALE HERE WAS USED, BUT ITS JUST THE SAME VALUES
		modelmatrixColliderSpider5 = glm::scale(modelmatrixColliderSpider5, glm::vec3(0.1f));
		modelmatrixColliderSpider5 = glm::translate(modelmatrixColliderSpider5,
				glm::vec3(spiderModelAnimate.getObb().c.x,
						spiderModelAnimate.getObb().c.y,
						spiderModelAnimate.getObb().c.z));
						//QUI TAMBIEN SE USO MCSCALE
		Spider5Collider.e = spiderModelAnimate.getObb().e * glm::vec3(0.1f) * glm::vec3(0.787401574, 0.787401574, 0.787401574);
		Spider5Collider.c = glm::vec3(modelmatrixColliderSpider5[3]);
		addOrUpdateColliders(collidersOBB, "Spider5", Spider5Collider, modelMatrixSpider5);


		// Collider de tiendas (parte menor)
		glm::mat4 modelMatrixColliderTiendas1= glm::mat4(matrixModelTiendas1);
		AbstractModel::OBB Tiendas1Collider;
		// Set the orientation of collider before doing the scale
		Tiendas1Collider.u = glm::quat_cast(matrixModelTiendas1);
		modelMatrixColliderTiendas1 = glm::scale(modelMatrixColliderTiendas1, glm::vec3(1.01));
		modelMatrixColliderTiendas1 = glm::translate(modelMatrixColliderTiendas1, 
						glm::vec3(modelTiendas1.getObb().c.x,
						modelTiendas1.getObb().c.y,
						modelTiendas1.getObb().c.z));
		Tiendas1Collider.c = glm::vec3(modelMatrixColliderTiendas1[3]);
		Tiendas1Collider.e = modelTiendas1.getObb().e * glm::vec3(1.0);
		addOrUpdateColliders(collidersOBB, "tiendas1", Tiendas1Collider, matrixModelTiendas1);
		
		// Collider de tiendas (parte mayor)
		glm::mat4 modelMatrixColliderTiendas2= glm::mat4(matrixModelTiendas2);
		AbstractModel::OBB Tiendas2Collider;
		// Set the orientation of collider before doing the scale
		Tiendas2Collider.u = glm::quat_cast(matrixModelTiendas2);
		modelMatrixColliderTiendas2 = glm::scale(modelMatrixColliderTiendas2, glm::vec3(1.0));
		modelMatrixColliderTiendas2 = glm::translate(modelMatrixColliderTiendas2, 
						glm::vec3(modelTiendas2.getObb().c.x,
						modelTiendas2.getObb().c.y,
						modelTiendas2.getObb().c.z));
		Tiendas2Collider.c = glm::vec3(modelMatrixColliderTiendas2[3]);
		Tiendas2Collider.e = modelTiendas2.getObb().e * glm::vec3(0.995);
		addOrUpdateColliders(collidersOBB, "Tiendas2", Tiendas2Collider, matrixModelTiendas2);

		// Collider de tiendas (parte mayor) VERSION OPUESTA
		glm::mat4 modelMatrixColliderTiendas2Ext= glm::mat4(matrixModelTiendas2Ext);
		AbstractModel::OBB Tiendas2ExtCollider;
		// Set the orientation of collider before doing the scale
		Tiendas2ExtCollider.u = glm::quat_cast(matrixModelTiendas2Ext);
		modelMatrixColliderTiendas2Ext = glm::scale(modelMatrixColliderTiendas2Ext, glm::vec3(1.0));
		modelMatrixColliderTiendas2Ext = glm::translate(modelMatrixColliderTiendas2Ext, 
						glm::vec3(modelTiendas2.getObb().c.x,
						modelTiendas2.getObb().c.y,
						modelTiendas2.getObb().c.z));
		Tiendas2ExtCollider.c = glm::vec3(modelMatrixColliderTiendas2Ext[3]);
		Tiendas2ExtCollider.e = modelTiendas2.getObb().e * glm::vec3(0.999);
		addOrUpdateColliders(collidersOBB, "Tiendas2Ext", Tiendas2ExtCollider, matrixModelTiendas2Ext);

		// Collider de tiendas (parte menor) VERSION OPUESTA
		glm::mat4 modelMatrixColliderTiendas1Ext= glm::mat4(matrixModelTiendas1Ext);
		AbstractModel::OBB Tiendas1ExtCollider;
		// Set the orientation of collider before doing the scale
		Tiendas1ExtCollider.u = glm::quat_cast(matrixModelTiendas1Ext);
		modelMatrixColliderTiendas1Ext = glm::scale(modelMatrixColliderTiendas1Ext, glm::vec3(1.01));
		modelMatrixColliderTiendas1Ext = glm::translate(modelMatrixColliderTiendas1Ext, 
						glm::vec3(modelTiendas1.getObb().c.x,
						modelTiendas1.getObb().c.y,
						modelTiendas1.getObb().c.z));
		Tiendas1ExtCollider.c = glm::vec3(modelMatrixColliderTiendas1Ext[3]);
		Tiendas1ExtCollider.e = modelTiendas1.getObb().e * glm::vec3(1.0);
		addOrUpdateColliders(collidersOBB, "Tiendas1Ext", Tiendas1ExtCollider, matrixModelTiendas1Ext);

		// Collider de Puerta de salida
		glm::mat4 modelMatrixColliderTiendasSalida= glm::mat4(matrixModelTiendasSalida);
		AbstractModel::OBB TiendasSalidaCollider;
		// Set the orientation of collider before doing the scale
		TiendasSalidaCollider.u = glm::quat_cast(matrixModelTiendasSalida);
		modelMatrixColliderTiendasSalida = glm::scale(modelMatrixColliderTiendasSalida, glm::vec3(0.1029f,0.1029f,0.5029f));
		//modelMatrixColliderTiendasSalida = glm::rotate(modelMatrixColliderTiendasSalida, glm::radians(90.0f), glm::vec3(0,0,1));
		modelMatrixColliderTiendasSalida = glm::translate(modelMatrixColliderTiendasSalida, 
						glm::vec3(modelTiendasSalida.getObb().c.x,
						modelTiendasSalida.getObb().c.y,
						modelTiendasSalida.getObb().c.z));
		TiendasSalidaCollider.c = glm::vec3(modelMatrixColliderTiendasSalida[3]);
		TiendasSalidaCollider.e = modelTiendasSalida.getObb().e * glm::vec3(0.00219f);
		addOrUpdateColliders(collidersOBB, "TiendasSalida", TiendasSalidaCollider, matrixModelTiendasSalida);


		// Botes de basura (par)
		//Por alguna razon el collider es mas largo de lo que deberia ser, asi que lo estoy haciendo
		//mas chico en la linea de BasuraCollider.e
		glm::mat4 modelMatrixColliderBasura= glm::mat4(matrixModelBasura);
		AbstractModel::OBB BasuraCollider;
		// Set the orientation of collider before doing the scale
		BasuraCollider.u = glm::quat_cast(matrixModelBasura);
		modelMatrixColliderBasura = glm::scale(modelMatrixColliderBasura, glm::vec3(0.001f,1.0f,1.0f));
		modelMatrixColliderBasura = glm::translate(modelMatrixColliderBasura, 
						glm::vec3(modelBasura.getObb().c.x,
						modelBasura.getObb().c.y,
						modelBasura.getObb().c.z));
		BasuraCollider.c = glm::vec3(modelMatrixColliderBasura[3]);
		BasuraCollider.e = modelBasura.getObb().e * glm::vec3(0.011f);
		addOrUpdateColliders(collidersOBB, "Basura", BasuraCollider, matrixModelBasura);


		//SET DE COLLIDERS PARA MUEBLES
		/****************************************************/

		// Collider de Muebles1
		glm::mat4 modelMatrixColliderMuebles= glm::mat4(matrixModelMuebles);
		AbstractModel::OBB MueblesCollider;
		// Set the orientation of collider before doing the scale
		MueblesCollider.u = glm::quat_cast(matrixModelMuebles);
		modelMatrixColliderMuebles = glm::scale(modelMatrixColliderMuebles, glm::vec3(0.1f));
		modelMatrixColliderMuebles = glm::translate(modelMatrixColliderMuebles, 
						glm::vec3(modelMuebles.getObb().c.x,
						modelMuebles.getObb().c.y,
						modelMuebles.getObb().c.z));
		MueblesCollider.c = glm::vec3(modelMatrixColliderMuebles[3]);
		MueblesCollider.e = modelMuebles.getObb().e * glm::vec3(0.01f);
		addOrUpdateColliders(collidersOBB, "Muebles", MueblesCollider, matrixModelMuebles);

		// Collider de Muebles2
		glm::mat4 modelMatrixColliderMuebles2= glm::mat4(matrixModelMuebles2);
		AbstractModel::OBB Muebles2Collider;
		// Set the orientation of collider before doing the scale
		Muebles2Collider.u = glm::quat_cast(matrixModelMuebles2);
		modelMatrixColliderMuebles2 = glm::scale(modelMatrixColliderMuebles2, glm::vec3(0.1f));
		modelMatrixColliderMuebles2 = glm::translate(modelMatrixColliderMuebles2, 
						glm::vec3(modelMuebles.getObb().c.x,
						modelMuebles.getObb().c.y,
						modelMuebles.getObb().c.z));
		Muebles2Collider.c = glm::vec3(modelMatrixColliderMuebles2[3]);
		Muebles2Collider.e = modelMuebles.getObb().e * glm::vec3(0.01f);
		addOrUpdateColliders(collidersOBB, "Muebles2", Muebles2Collider, matrixModelMuebles2);

		// Collider de Muebles3
		glm::mat4 modelMatrixColliderMuebles3= glm::mat4(matrixModelMuebles3);
		AbstractModel::OBB Muebles3Collider;
		// Set the orientation of collider before doing the scale
		Muebles3Collider.u = glm::quat_cast(matrixModelMuebles3);
		modelMatrixColliderMuebles3 = glm::scale(modelMatrixColliderMuebles3, glm::vec3(0.1f));
		modelMatrixColliderMuebles3 = glm::translate(modelMatrixColliderMuebles3, 
						glm::vec3(modelMuebles.getObb().c.x,
						modelMuebles.getObb().c.y,
						modelMuebles.getObb().c.z));
		Muebles3Collider.c = glm::vec3(modelMatrixColliderMuebles3[3]);
		Muebles3Collider.e = modelMuebles.getObb().e * glm::vec3(0.01f);
		addOrUpdateColliders(collidersOBB, "Muebles3", Muebles3Collider, matrixModelMuebles3);

		// Collider de Muebles4
		glm::mat4 modelMatrixColliderMuebles4= glm::mat4(matrixModelMuebles4);
		AbstractModel::OBB Muebles4Collider;
		// Set the orientation of collider before doing the scale
		Muebles4Collider.u = glm::quat_cast(matrixModelMuebles4);
		modelMatrixColliderMuebles4 = glm::scale(modelMatrixColliderMuebles4, glm::vec3(0.1f));
		modelMatrixColliderMuebles4 = glm::translate(modelMatrixColliderMuebles4, 
						glm::vec3(modelMuebles.getObb().c.x,
						modelMuebles.getObb().c.y,
						modelMuebles.getObb().c.z));
		Muebles4Collider.c = glm::vec3(modelMatrixColliderMuebles4[3]);
		Muebles4Collider.e = modelMuebles.getObb().e * glm::vec3(0.01f);
		addOrUpdateColliders(collidersOBB, "Muebles4", Muebles4Collider, matrixModelMuebles4);

		// Collider de Muebles5
		glm::mat4 modelMatrixColliderMuebles5= glm::mat4(matrixModelMuebles5);
		AbstractModel::OBB Muebles5Collider;
		// Set the orientation of collider before doing the scale
		Muebles5Collider.u = glm::quat_cast(matrixModelMuebles5);
		modelMatrixColliderMuebles5 = glm::scale(modelMatrixColliderMuebles5, glm::vec3(0.1f));
		modelMatrixColliderMuebles5 = glm::translate(modelMatrixColliderMuebles5, 
						glm::vec3(modelMuebles.getObb().c.x,
						modelMuebles.getObb().c.y,
						modelMuebles.getObb().c.z));
		Muebles5Collider.c = glm::vec3(modelMatrixColliderMuebles5[3]);
		Muebles5Collider.e = modelMuebles.getObb().e * glm::vec3(0.01f);
		addOrUpdateColliders(collidersOBB, "Muebles5", Muebles5Collider, matrixModelMuebles5);

		// Collider de Muebles6
		glm::mat4 modelMatrixColliderMuebles6= glm::mat4(matrixModelMuebles6);
		AbstractModel::OBB Muebles6Collider;
		// Set the orientation of collider before doing the scale
		Muebles6Collider.u = glm::quat_cast(matrixModelMuebles6);
		modelMatrixColliderMuebles6 = glm::scale(modelMatrixColliderMuebles6, glm::vec3(0.1f));
		modelMatrixColliderMuebles6 = glm::translate(modelMatrixColliderMuebles6, 
						glm::vec3(modelMuebles.getObb().c.x,
						modelMuebles.getObb().c.y,
						modelMuebles.getObb().c.z));
		Muebles6Collider.c = glm::vec3(modelMatrixColliderMuebles6[3]);
		Muebles6Collider.e = modelMuebles.getObb().e * glm::vec3(0.01f);
		addOrUpdateColliders(collidersOBB, "Muebles6", Muebles6Collider, matrixModelMuebles6);

		// Collider de Muebles7
		glm::mat4 modelMatrixColliderMuebles7= glm::mat4(matrixModelMuebles7);
		AbstractModel::OBB Muebles7Collider;
		// Set the orientation of collider before doing the scale
		Muebles7Collider.u = glm::quat_cast(matrixModelMuebles7);
		modelMatrixColliderMuebles7 = glm::scale(modelMatrixColliderMuebles7, glm::vec3(0.1f));
		modelMatrixColliderMuebles7 = glm::translate(modelMatrixColliderMuebles7, 
						glm::vec3(modelMuebles.getObb().c.x,
						modelMuebles.getObb().c.y,
						modelMuebles.getObb().c.z));
		Muebles7Collider.c = glm::vec3(modelMatrixColliderMuebles7[3]);
		Muebles7Collider.e = modelMuebles.getObb().e * glm::vec3(0.01f);
		addOrUpdateColliders(collidersOBB, "Muebles7", Muebles7Collider, matrixModelMuebles7);

		// Collider de Muebles8
		glm::mat4 modelMatrixColliderMuebles8= glm::mat4(matrixModelMuebles8);
		AbstractModel::OBB Muebles8Collider;
		// Set the orientation of collider before doing the scale
		Muebles8Collider.u = glm::quat_cast(matrixModelMuebles8);
		modelMatrixColliderMuebles8 = glm::scale(modelMatrixColliderMuebles8, glm::vec3(0.1f));
		modelMatrixColliderMuebles8 = glm::translate(modelMatrixColliderMuebles8, 
						glm::vec3(modelMuebles.getObb().c.x,
						modelMuebles.getObb().c.y,
						modelMuebles.getObb().c.z));
		Muebles8Collider.c = glm::vec3(modelMatrixColliderMuebles8[3]);
		Muebles8Collider.e = modelMuebles.getObb().e * glm::vec3(0.01f);
		addOrUpdateColliders(collidersOBB, "Muebles8", Muebles8Collider, matrixModelMuebles8);

		// Collider de Muebles9
		glm::mat4 modelMatrixColliderMuebles9= glm::mat4(matrixModelMuebles9);
		AbstractModel::OBB Muebles9Collider;
		// Set the orientation of collider before doing the scale
		Muebles9Collider.u = glm::quat_cast(matrixModelMuebles9);
		modelMatrixColliderMuebles9 = glm::scale(modelMatrixColliderMuebles9, glm::vec3(0.1f));
		modelMatrixColliderMuebles9 = glm::translate(modelMatrixColliderMuebles9, 
						glm::vec3(modelMuebles.getObb().c.x,
						modelMuebles.getObb().c.y,
						modelMuebles.getObb().c.z));
		Muebles9Collider.c = glm::vec3(modelMatrixColliderMuebles9[3]);
		Muebles9Collider.e = modelMuebles.getObb().e * glm::vec3(0.01f);
		addOrUpdateColliders(collidersOBB, "Muebles9", Muebles9Collider, matrixModelMuebles9);

		// Collider de Muebles10
		glm::mat4 modelMatrixColliderMuebles10= glm::mat4(matrixModelMuebles10);
		AbstractModel::OBB Muebles10Collider;
		// Set the orientation of collider before doing the scale
		Muebles10Collider.u = glm::quat_cast(matrixModelMuebles10);
		modelMatrixColliderMuebles10 = glm::scale(modelMatrixColliderMuebles10, glm::vec3(0.1f));
		modelMatrixColliderMuebles10 = glm::translate(modelMatrixColliderMuebles10, 
						glm::vec3(modelMuebles.getObb().c.x,
						modelMuebles.getObb().c.y,
						modelMuebles.getObb().c.z));
		Muebles10Collider.c = glm::vec3(modelMatrixColliderMuebles10[3]);
		Muebles10Collider.e = modelMuebles.getObb().e * glm::vec3(0.01f);
		addOrUpdateColliders(collidersOBB, "Muebles10", Muebles10Collider, matrixModelMuebles10);

		// Collider de Muebles11
		glm::mat4 modelMatrixColliderMuebles11= glm::mat4(matrixModelMuebles11);
		AbstractModel::OBB Muebles11Collider;
		// Set the orientation of collider before doing the scale
		Muebles11Collider.u = glm::quat_cast(matrixModelMuebles11);
		modelMatrixColliderMuebles11 = glm::scale(modelMatrixColliderMuebles11, glm::vec3(0.1f));
		modelMatrixColliderMuebles11 = glm::translate(modelMatrixColliderMuebles11, 
						glm::vec3(modelMuebles.getObb().c.x,
						modelMuebles.getObb().c.y,
						modelMuebles.getObb().c.z));
		Muebles11Collider.c = glm::vec3(modelMatrixColliderMuebles11[3]);
		Muebles11Collider.e = modelMuebles.getObb().e * glm::vec3(0.01f);
		addOrUpdateColliders(collidersOBB, "Muebles11", Muebles11Collider, matrixModelMuebles11);

		// Collider de Muebles12
		glm::mat4 modelMatrixColliderMuebles12= glm::mat4(matrixModelMuebles12);
		AbstractModel::OBB Muebles12Collider;
		// Set the orientation of collider before doing the scale
		Muebles12Collider.u = glm::quat_cast(matrixModelMuebles12);
		modelMatrixColliderMuebles12 = glm::scale(modelMatrixColliderMuebles12, glm::vec3(0.1f));
		modelMatrixColliderMuebles12 = glm::translate(modelMatrixColliderMuebles12, 
						glm::vec3(modelMuebles.getObb().c.x,
						modelMuebles.getObb().c.y,
						modelMuebles.getObb().c.z));
		Muebles12Collider.c = glm::vec3(modelMatrixColliderMuebles12[3]);
		Muebles12Collider.e = modelMuebles.getObb().e * glm::vec3(0.01f);
		addOrUpdateColliders(collidersOBB, "Muebles12", Muebles12Collider, matrixModelMuebles12);

		// Collider de Muebles13
		glm::mat4 modelMatrixColliderMuebles13= glm::mat4(matrixModelMuebles13);
		AbstractModel::OBB Muebles13Collider;
		// Set the orientation of collider before doing the scale
		Muebles13Collider.u = glm::quat_cast(matrixModelMuebles13);
		modelMatrixColliderMuebles13 = glm::scale(modelMatrixColliderMuebles13, glm::vec3(0.1f));
		modelMatrixColliderMuebles13 = glm::translate(modelMatrixColliderMuebles13, 
						glm::vec3(modelMuebles.getObb().c.x,
						modelMuebles.getObb().c.y,
						modelMuebles.getObb().c.z));
		Muebles13Collider.c = glm::vec3(modelMatrixColliderMuebles13[3]);
		Muebles13Collider.e = modelMuebles.getObb().e * glm::vec3(0.01f);
		addOrUpdateColliders(collidersOBB, "Muebles13", Muebles13Collider, matrixModelMuebles13);

		// Collider de Muebles14
		glm::mat4 modelMatrixColliderMuebles14= glm::mat4(matrixModelMuebles14);
		AbstractModel::OBB Muebles14Collider;
		// Set the orientation of collider before doing the scale
		Muebles14Collider.u = glm::quat_cast(matrixModelMuebles14);
		modelMatrixColliderMuebles14 = glm::scale(modelMatrixColliderMuebles14, glm::vec3(0.1f));
		modelMatrixColliderMuebles14 = glm::translate(modelMatrixColliderMuebles14, 
						glm::vec3(modelMuebles.getObb().c.x,
						modelMuebles.getObb().c.y,
						modelMuebles.getObb().c.z));
		Muebles14Collider.c = glm::vec3(modelMatrixColliderMuebles14[3]);
		Muebles14Collider.e = modelMuebles.getObb().e * glm::vec3(0.01f);
		addOrUpdateColliders(collidersOBB, "Muebles14", Muebles14Collider, matrixModelMuebles14);

		// Collider de Muebles15
		glm::mat4 modelMatrixColliderMuebles15= glm::mat4(matrixModelMuebles15);
		AbstractModel::OBB Muebles15Collider;
		// Set the orientation of collider before doing the scale
		Muebles15Collider.u = glm::quat_cast(matrixModelMuebles15);
		modelMatrixColliderMuebles15 = glm::scale(modelMatrixColliderMuebles15, glm::vec3(0.1f));
		modelMatrixColliderMuebles15 = glm::translate(modelMatrixColliderMuebles15, 
						glm::vec3(modelMuebles.getObb().c.x,
						modelMuebles.getObb().c.y,
						modelMuebles.getObb().c.z));
		Muebles15Collider.c = glm::vec3(modelMatrixColliderMuebles15[3]);
		Muebles15Collider.e = modelMuebles.getObb().e * glm::vec3(0.01f);
		addOrUpdateColliders(collidersOBB, "Muebles15", Muebles15Collider, matrixModelMuebles15);

		// Collider de Muebles16
		glm::mat4 modelMatrixColliderMuebles16= glm::mat4(matrixModelMuebles16);
		AbstractModel::OBB Muebles16Collider;
		// Set the orientation of collider before doing the scale
		Muebles16Collider.u = glm::quat_cast(matrixModelMuebles16);
		modelMatrixColliderMuebles16 = glm::scale(modelMatrixColliderMuebles16, glm::vec3(0.1f));
		modelMatrixColliderMuebles16 = glm::translate(modelMatrixColliderMuebles16, 
						glm::vec3(modelMuebles.getObb().c.x,
						modelMuebles.getObb().c.y,
						modelMuebles.getObb().c.z));
		Muebles16Collider.c = glm::vec3(modelMatrixColliderMuebles16[3]);
		Muebles16Collider.e = modelMuebles.getObb().e * glm::vec3(0.01f);
		addOrUpdateColliders(collidersOBB, "Muebles16", Muebles16Collider, matrixModelMuebles16);

		// Collider de Muebles17
		glm::mat4 modelMatrixColliderMuebles17= glm::mat4(matrixModelMuebles17);
		AbstractModel::OBB Muebles17Collider;
		// Set the orientation of collider before doing the scale
		Muebles17Collider.u = glm::quat_cast(matrixModelMuebles17);
		modelMatrixColliderMuebles17 = glm::scale(modelMatrixColliderMuebles17, glm::vec3(0.1f));
		modelMatrixColliderMuebles17 = glm::translate(modelMatrixColliderMuebles17, 
						glm::vec3(modelMuebles.getObb().c.x,
						modelMuebles.getObb().c.y,
						modelMuebles.getObb().c.z));
		Muebles17Collider.c = glm::vec3(modelMatrixColliderMuebles17[3]);
		Muebles17Collider.e = modelMuebles.getObb().e * glm::vec3(0.01f);
		addOrUpdateColliders(collidersOBB, "Muebles17", Muebles17Collider, matrixModelMuebles17);

		// Collider de Muebles18
		glm::mat4 modelMatrixColliderMuebles18= glm::mat4(matrixModelMuebles18);
		AbstractModel::OBB Muebles18Collider;
		// Set the orientation of collider before doing the scale
		Muebles18Collider.u = glm::quat_cast(matrixModelMuebles18);
		modelMatrixColliderMuebles18 = glm::scale(modelMatrixColliderMuebles18, glm::vec3(0.1f));
		modelMatrixColliderMuebles18 = glm::translate(modelMatrixColliderMuebles18, 
						glm::vec3(modelMuebles.getObb().c.x,
						modelMuebles.getObb().c.y,
						modelMuebles.getObb().c.z));
		Muebles18Collider.c = glm::vec3(modelMatrixColliderMuebles18[3]);
		Muebles18Collider.e = modelMuebles.getObb().e * glm::vec3(0.01f);
		addOrUpdateColliders(collidersOBB, "Muebles18", Muebles18Collider, matrixModelMuebles18);

		// Collider de Muebles19
		glm::mat4 modelMatrixColliderMuebles19= glm::mat4(matrixModelMuebles19);
		AbstractModel::OBB Muebles19Collider;
		// Set the orientation of collider before doing the scale
		Muebles19Collider.u = glm::quat_cast(matrixModelMuebles19);
		modelMatrixColliderMuebles19 = glm::scale(modelMatrixColliderMuebles19, glm::vec3(0.1f));
		modelMatrixColliderMuebles19 = glm::translate(modelMatrixColliderMuebles19, 
						glm::vec3(modelMuebles.getObb().c.x,
						modelMuebles.getObb().c.y,
						modelMuebles.getObb().c.z));
		Muebles19Collider.c = glm::vec3(modelMatrixColliderMuebles19[3]);
		Muebles19Collider.e = modelMuebles.getObb().e * glm::vec3(0.01f);
		addOrUpdateColliders(collidersOBB, "Muebles19", Muebles19Collider, matrixModelMuebles19);

		// Collider de Muebles20
		glm::mat4 modelMatrixColliderMuebles20= glm::mat4(matrixModelMuebles20);
		AbstractModel::OBB Muebles20Collider;
		// Set the orientation of collider before doing the scale
		Muebles20Collider.u = glm::quat_cast(matrixModelMuebles20);
		modelMatrixColliderMuebles20 = glm::scale(modelMatrixColliderMuebles20, glm::vec3(0.1f));
		modelMatrixColliderMuebles20 = glm::translate(modelMatrixColliderMuebles20, 
						glm::vec3(modelMuebles.getObb().c.x,
						modelMuebles.getObb().c.y,
						modelMuebles.getObb().c.z));
		Muebles20Collider.c = glm::vec3(modelMatrixColliderMuebles20[3]);
		Muebles20Collider.e = modelMuebles.getObb().e * glm::vec3(0.01f);
		addOrUpdateColliders(collidersOBB, "Muebles20", Muebles20Collider, matrixModelMuebles20);

		// Collider de Muebles21
		glm::mat4 modelMatrixColliderMuebles21= glm::mat4(matrixModelMuebles21);
		AbstractModel::OBB Muebles21Collider;
		// Set the orientation of collider before doing the scale
		Muebles21Collider.u = glm::quat_cast(matrixModelMuebles21);
		modelMatrixColliderMuebles21 = glm::scale(modelMatrixColliderMuebles21, glm::vec3(0.1f));
		modelMatrixColliderMuebles21 = glm::translate(modelMatrixColliderMuebles21, 
						glm::vec3(modelMuebles.getObb().c.x,
						modelMuebles.getObb().c.y,
						modelMuebles.getObb().c.z));
		Muebles21Collider.c = glm::vec3(modelMatrixColliderMuebles21[3]);
		Muebles21Collider.e = modelMuebles.getObb().e * glm::vec3(0.01f);
		addOrUpdateColliders(collidersOBB, "Muebles21", Muebles21Collider, matrixModelMuebles21);

		// Collider de Muebles22
		glm::mat4 modelMatrixColliderMuebles22= glm::mat4(matrixModelMuebles22);
		AbstractModel::OBB Muebles22Collider;
		// Set the orientation of collider before doing the scale
		Muebles22Collider.u = glm::quat_cast(matrixModelMuebles22);
		modelMatrixColliderMuebles22 = glm::scale(modelMatrixColliderMuebles22, glm::vec3(0.1f));
		modelMatrixColliderMuebles22 = glm::translate(modelMatrixColliderMuebles22, 
						glm::vec3(modelMuebles.getObb().c.x,
						modelMuebles.getObb().c.y,
						modelMuebles.getObb().c.z));
		Muebles22Collider.c = glm::vec3(modelMatrixColliderMuebles22[3]);
		Muebles22Collider.e = modelMuebles.getObb().e * glm::vec3(0.01f);
		addOrUpdateColliders(collidersOBB, "Muebles22", Muebles22Collider, matrixModelMuebles22);

		// Collider de Muebles23
		glm::mat4 modelMatrixColliderMuebles23= glm::mat4(matrixModelMuebles23);
		AbstractModel::OBB Muebles23Collider;
		// Set the orientation of collider before doing the scale
		Muebles23Collider.u = glm::quat_cast(matrixModelMuebles23);
		modelMatrixColliderMuebles23 = glm::scale(modelMatrixColliderMuebles23, glm::vec3(0.1f));
		modelMatrixColliderMuebles23 = glm::translate(modelMatrixColliderMuebles23, 
						glm::vec3(modelMuebles.getObb().c.x,
						modelMuebles.getObb().c.y,
						modelMuebles.getObb().c.z));
		Muebles23Collider.c = glm::vec3(modelMatrixColliderMuebles23[3]);
		Muebles23Collider.e = modelMuebles.getObb().e * glm::vec3(0.01f);
		addOrUpdateColliders(collidersOBB, "Muebles23", Muebles23Collider, matrixModelMuebles23);

		// Collider de Muebles24
		glm::mat4 modelMatrixColliderMuebles24= glm::mat4(matrixModelMuebles24);
		AbstractModel::OBB Muebles24Collider;
		// Set the orientation of collider before doing the scale
		Muebles24Collider.u = glm::quat_cast(matrixModelMuebles24);
		modelMatrixColliderMuebles24 = glm::scale(modelMatrixColliderMuebles24, glm::vec3(0.1f));
		modelMatrixColliderMuebles24 = glm::translate(modelMatrixColliderMuebles24, 
						glm::vec3(modelMuebles.getObb().c.x,
						modelMuebles.getObb().c.y,
						modelMuebles.getObb().c.z));
		Muebles24Collider.c = glm::vec3(modelMatrixColliderMuebles24[3]);
		Muebles24Collider.e = modelMuebles.getObb().e * glm::vec3(0.01f);
		addOrUpdateColliders(collidersOBB, "Muebles24", Muebles24Collider, matrixModelMuebles24);

		// Collider de Muebles25
		glm::mat4 modelMatrixColliderMuebles25= glm::mat4(matrixModelMuebles25);
		AbstractModel::OBB Muebles25Collider;
		// Set the orientation of collider before doing the scale
		Muebles25Collider.u = glm::quat_cast(matrixModelMuebles25);
		modelMatrixColliderMuebles25 = glm::scale(modelMatrixColliderMuebles25, glm::vec3(0.1f));
		modelMatrixColliderMuebles25 = glm::translate(modelMatrixColliderMuebles25, 
						glm::vec3(modelMuebles.getObb().c.x,
						modelMuebles.getObb().c.y,
						modelMuebles.getObb().c.z));
		Muebles25Collider.c = glm::vec3(modelMatrixColliderMuebles25[3]);
		Muebles25Collider.e = modelMuebles.getObb().e * glm::vec3(0.01f);
		addOrUpdateColliders(collidersOBB, "Muebles25", Muebles25Collider, matrixModelMuebles25);

		// Collider de Muebles26
		glm::mat4 modelMatrixColliderMuebles26= glm::mat4(matrixModelMuebles26);
		AbstractModel::OBB Muebles26Collider;
		// Set the orientation of collider before doing the scale
		Muebles26Collider.u = glm::quat_cast(matrixModelMuebles26);
		modelMatrixColliderMuebles26 = glm::scale(modelMatrixColliderMuebles26, glm::vec3(0.1f));
		modelMatrixColliderMuebles26 = glm::translate(modelMatrixColliderMuebles26, 
						glm::vec3(modelMuebles.getObb().c.x,
						modelMuebles.getObb().c.y,
						modelMuebles.getObb().c.z));
		Muebles26Collider.c = glm::vec3(modelMatrixColliderMuebles26[3]);
		Muebles26Collider.e = modelMuebles.getObb().e * glm::vec3(0.01f);
		addOrUpdateColliders(collidersOBB, "Muebles26", Muebles26Collider, matrixModelMuebles26);

		// Collider de Muebles27
		glm::mat4 modelMatrixColliderMuebles27= glm::mat4(matrixModelMuebles27);
		AbstractModel::OBB Muebles27Collider;
		// Set the orientation of collider before doing the scale
		Muebles27Collider.u = glm::quat_cast(matrixModelMuebles27);
		modelMatrixColliderMuebles27 = glm::scale(modelMatrixColliderMuebles27, glm::vec3(0.1f));
		modelMatrixColliderMuebles27 = glm::translate(modelMatrixColliderMuebles27, 
						glm::vec3(modelMuebles.getObb().c.x,
						modelMuebles.getObb().c.y,
						modelMuebles.getObb().c.z));
		Muebles27Collider.c = glm::vec3(modelMatrixColliderMuebles27[3]);
		Muebles27Collider.e = modelMuebles.getObb().e * glm::vec3(0.01f);
		addOrUpdateColliders(collidersOBB, "Muebles27", Muebles27Collider, matrixModelMuebles27);

		// Collider de Muebles28
		glm::mat4 modelMatrixColliderMuebles28= glm::mat4(matrixModelMuebles28);
		AbstractModel::OBB Muebles28Collider;
		// Set the orientation of collider before doing the scale
		Muebles28Collider.u = glm::quat_cast(matrixModelMuebles28);
		modelMatrixColliderMuebles28 = glm::scale(modelMatrixColliderMuebles28, glm::vec3(0.1f));
		modelMatrixColliderMuebles28 = glm::translate(modelMatrixColliderMuebles28, 
						glm::vec3(modelMuebles.getObb().c.x,
						modelMuebles.getObb().c.y,
						modelMuebles.getObb().c.z));
		Muebles28Collider.c = glm::vec3(modelMatrixColliderMuebles28[3]);
		Muebles28Collider.e = modelMuebles.getObb().e * glm::vec3(0.01f);
		addOrUpdateColliders(collidersOBB, "Muebles28", Muebles28Collider, matrixModelMuebles28);

		// Collider de Muebles29
		glm::mat4 modelMatrixColliderMuebles29= glm::mat4(matrixModelMuebles29);
		AbstractModel::OBB Muebles29Collider;
		// Set the orientation of collider before doing the scale
		Muebles29Collider.u = glm::quat_cast(matrixModelMuebles29);
		modelMatrixColliderMuebles29 = glm::scale(modelMatrixColliderMuebles29, glm::vec3(0.1f));
		modelMatrixColliderMuebles29 = glm::translate(modelMatrixColliderMuebles29, 
						glm::vec3(modelMuebles.getObb().c.x,
						modelMuebles.getObb().c.y,
						modelMuebles.getObb().c.z));
		Muebles29Collider.c = glm::vec3(modelMatrixColliderMuebles29[3]);
		Muebles29Collider.e = modelMuebles.getObb().e * glm::vec3(0.01f);
		addOrUpdateColliders(collidersOBB, "Muebles29", Muebles29Collider, matrixModelMuebles29);

		// Collider de Muebles30
		glm::mat4 modelMatrixColliderMuebles30= glm::mat4(matrixModelMuebles30);
		AbstractModel::OBB Muebles30Collider;
		// Set the orientation of collider before doing the scale
		Muebles30Collider.u = glm::quat_cast(matrixModelMuebles30);
		modelMatrixColliderMuebles30 = glm::scale(modelMatrixColliderMuebles30, glm::vec3(0.1f));
		modelMatrixColliderMuebles30 = glm::translate(modelMatrixColliderMuebles30, 
						glm::vec3(modelMuebles.getObb().c.x,
						modelMuebles.getObb().c.y,
						modelMuebles.getObb().c.z));
		Muebles30Collider.c = glm::vec3(modelMatrixColliderMuebles30[3]);
		Muebles30Collider.e = modelMuebles.getObb().e * glm::vec3(0.01f);
		addOrUpdateColliders(collidersOBB, "Muebles30", Muebles30Collider, matrixModelMuebles30);

		// Collider de Muebles31
		glm::mat4 modelMatrixColliderMuebles31= glm::mat4(matrixModelMuebles31);
		AbstractModel::OBB Muebles31Collider;
		// Set the orientation of collider before doing the scale
		Muebles31Collider.u = glm::quat_cast(matrixModelMuebles31);
		modelMatrixColliderMuebles31 = glm::scale(modelMatrixColliderMuebles31, glm::vec3(0.1f));
		modelMatrixColliderMuebles31 = glm::translate(modelMatrixColliderMuebles31, 
						glm::vec3(modelMuebles.getObb().c.x,
						modelMuebles.getObb().c.y,
						modelMuebles.getObb().c.z));
		Muebles31Collider.c = glm::vec3(modelMatrixColliderMuebles31[3]);
		Muebles31Collider.e = modelMuebles.getObb().e * glm::vec3(0.01f);
		addOrUpdateColliders(collidersOBB, "Muebles31", Muebles31Collider, matrixModelMuebles31);

		// Collider de Muebles32
		glm::mat4 modelMatrixColliderMuebles32= glm::mat4(matrixModelMuebles32);
		AbstractModel::OBB Muebles32Collider;
		// Set the orientation of collider before doing the scale
		Muebles32Collider.u = glm::quat_cast(matrixModelMuebles32);
		modelMatrixColliderMuebles32 = glm::scale(modelMatrixColliderMuebles32, glm::vec3(0.1f));
		modelMatrixColliderMuebles32 = glm::translate(modelMatrixColliderMuebles32, 
						glm::vec3(modelMuebles.getObb().c.x,
						modelMuebles.getObb().c.y,
						modelMuebles.getObb().c.z));
		Muebles32Collider.c = glm::vec3(modelMatrixColliderMuebles32[3]);
		Muebles32Collider.e = modelMuebles.getObb().e * glm::vec3(0.01f);
		addOrUpdateColliders(collidersOBB, "Muebles32", Muebles32Collider, matrixModelMuebles32);

		// Collider de Mueble33
		glm::mat4 modelMatrixColliderMuebles33= glm::mat4(matrixModelMuebles33);
		AbstractModel::OBB Muebles33Collider;
		// Set the orientation of collider before doing the scale
		Muebles33Collider.u = glm::quat_cast(matrixModelMuebles33);
		modelMatrixColliderMuebles33 = glm::scale(modelMatrixColliderMuebles33, glm::vec3(0.1f));
		modelMatrixColliderMuebles33 = glm::translate(modelMatrixColliderMuebles33, 
						glm::vec3(modelMuebles.getObb().c.x,
						modelMuebles.getObb().c.y,
						modelMuebles.getObb().c.z));
		Muebles33Collider.c = glm::vec3(modelMatrixColliderMuebles33[3]);
		Muebles33Collider.e = modelMuebles.getObb().e * glm::vec3(0.01f);
		addOrUpdateColliders(collidersOBB, "Muebles33", Muebles33Collider, matrixModelMuebles33);

		// Collider de Mueble34
		glm::mat4 modelMatrixColliderMuebles34= glm::mat4(matrixModelMuebles34);
		AbstractModel::OBB Muebles34Collider;
		// Set the orientation of collider before doing the scale
		Muebles34Collider.u = glm::quat_cast(matrixModelMuebles34);
		modelMatrixColliderMuebles34 = glm::scale(modelMatrixColliderMuebles34, glm::vec3(0.1f));
		modelMatrixColliderMuebles34 = glm::translate(modelMatrixColliderMuebles34, 
						glm::vec3(modelMuebles.getObb().c.x,
						modelMuebles.getObb().c.y,
						modelMuebles.getObb().c.z));
		Muebles34Collider.c = glm::vec3(modelMatrixColliderMuebles34[3]);
		Muebles34Collider.e = modelMuebles.getObb().e * glm::vec3(0.01f);
		addOrUpdateColliders(collidersOBB, "Muebles34", Muebles34Collider, matrixModelMuebles34);

		// Collider de Muebles35
		glm::mat4 modelMatrixColliderMuebles35= glm::mat4(matrixModelMuebles35);
		AbstractModel::OBB Muebles35Collider;
		// Set the orientation of collider before doing the scale
		Muebles35Collider.u = glm::quat_cast(matrixModelMuebles35);
		modelMatrixColliderMuebles35 = glm::scale(modelMatrixColliderMuebles35, glm::vec3(0.1f));
		modelMatrixColliderMuebles35 = glm::translate(modelMatrixColliderMuebles35, 
						glm::vec3(modelMuebles.getObb().c.x,
						modelMuebles.getObb().c.y,
						modelMuebles.getObb().c.z));
		Muebles35Collider.c = glm::vec3(modelMatrixColliderMuebles35[3]);
		Muebles35Collider.e = modelMuebles.getObb().e * glm::vec3(0.01f);
		addOrUpdateColliders(collidersOBB, "Muebles35", Muebles35Collider, matrixModelMuebles35);

		// Collider de Muebles36
		glm::mat4 modelMatrixColliderMuebles36= glm::mat4(matrixModelMuebles36);
		AbstractModel::OBB Muebles36Collider;
		// Set the orientation of collider before doing the scale
		Muebles36Collider.u = glm::quat_cast(matrixModelMuebles36);
		modelMatrixColliderMuebles36 = glm::scale(modelMatrixColliderMuebles36, glm::vec3(0.1f));
		modelMatrixColliderMuebles36 = glm::translate(modelMatrixColliderMuebles36, 
						glm::vec3(modelMuebles.getObb().c.x,
						modelMuebles.getObb().c.y,
						modelMuebles.getObb().c.z));
		Muebles36Collider.c = glm::vec3(modelMatrixColliderMuebles36[3]);
		Muebles36Collider.e = modelMuebles.getObb().e * glm::vec3(0.01f);
		addOrUpdateColliders(collidersOBB, "Muebles36", Muebles36Collider, matrixModelMuebles36);

		// Collider de MueblesExt1
		glm::mat4 modelMatrixColliderMueblesExt1= glm::mat4(matrixModelMueblesExt1);
		AbstractModel::OBB MueblesExt1Collider;
		// Set the orientation of collider before doing the scale
		MueblesExt1Collider.u = glm::quat_cast(matrixModelMueblesExt1);
		modelMatrixColliderMueblesExt1 = glm::scale(modelMatrixColliderMueblesExt1, glm::vec3(0.1f));
		modelMatrixColliderMueblesExt1 = glm::translate(modelMatrixColliderMueblesExt1, 
						glm::vec3(modelMuebles.getObb().c.x,
						modelMuebles.getObb().c.y,
						modelMuebles.getObb().c.z));
		MueblesExt1Collider.c = glm::vec3(modelMatrixColliderMueblesExt1[3]);
		MueblesExt1Collider.e = modelMuebles.getObb().e * glm::vec3(0.01f);
		addOrUpdateColliders(collidersOBB, "MueblesExt1", MueblesExt1Collider, matrixModelMueblesExt1);
		// Collider de MueblesExt2
		glm::mat4 modelMatrixColliderMueblesExt2= glm::mat4(matrixModelMueblesExt2);
		AbstractModel::OBB MueblesExt2Collider;
		// Set the orientation of collider before doing the scale
		MueblesExt2Collider.u = glm::quat_cast(matrixModelMueblesExt2);
		modelMatrixColliderMueblesExt2 = glm::scale(modelMatrixColliderMueblesExt2, glm::vec3(0.1f));
		modelMatrixColliderMueblesExt2 = glm::translate(modelMatrixColliderMueblesExt2, 
						glm::vec3(modelMuebles.getObb().c.x,
						modelMuebles.getObb().c.y,
						modelMuebles.getObb().c.z));
		MueblesExt2Collider.c = glm::vec3(modelMatrixColliderMueblesExt2[3]);
		MueblesExt2Collider.e = modelMuebles.getObb().e * glm::vec3(0.01f);
		addOrUpdateColliders(collidersOBB, "MueblesExt2", MueblesExt2Collider, matrixModelMueblesExt2);

		// Collider de MueblesExt3
		glm::mat4 modelMatrixColliderMueblesExt3= glm::mat4(matrixModelMueblesExt3);
		AbstractModel::OBB MueblesExt3Collider;
		// Set the orientation of collider before doing the scale
		MueblesExt3Collider.u = glm::quat_cast(matrixModelMueblesExt3);
		modelMatrixColliderMueblesExt3 = glm::scale(modelMatrixColliderMueblesExt3, glm::vec3(0.1f));
		modelMatrixColliderMueblesExt3 = glm::translate(modelMatrixColliderMueblesExt3, 
						glm::vec3(modelMuebles.getObb().c.x,
						modelMuebles.getObb().c.y,
						modelMuebles.getObb().c.z));
		MueblesExt3Collider.c = glm::vec3(modelMatrixColliderMueblesExt3[3]);
		MueblesExt3Collider.e = modelMuebles.getObb().e * glm::vec3(0.01f);
		addOrUpdateColliders(collidersOBB, "MueblesExt3", MueblesExt3Collider, matrixModelMueblesExt3);

		// Collider de MueblesExt4
		glm::mat4 modelMatrixColliderMueblesExt4= glm::mat4(matrixModelMueblesExt4);
		AbstractModel::OBB MueblesExt4Collider;
		// Set the orientation of collider before doing the scale
		MueblesExt4Collider.u = glm::quat_cast(matrixModelMueblesExt4);
		modelMatrixColliderMueblesExt4 = glm::scale(modelMatrixColliderMueblesExt4, glm::vec3(0.1f));
		modelMatrixColliderMueblesExt4 = glm::translate(modelMatrixColliderMueblesExt4, 
						glm::vec3(modelMuebles.getObb().c.x,
						modelMuebles.getObb().c.y,
						modelMuebles.getObb().c.z));
		MueblesExt4Collider.c = glm::vec3(modelMatrixColliderMueblesExt4[3]);
		MueblesExt4Collider.e = modelMuebles.getObb().e * glm::vec3(0.01f);
		addOrUpdateColliders(collidersOBB, "MueblesExt4", MueblesExt4Collider, matrixModelMueblesExt4);

		// Collider de MueblesExt5
		glm::mat4 modelMatrixColliderMueblesExt5= glm::mat4(matrixModelMueblesExt5);
		AbstractModel::OBB MueblesExt5Collider;
		// Set the orientation of collider before doing the scale
		MueblesExt5Collider.u = glm::quat_cast(matrixModelMueblesExt5);
		modelMatrixColliderMueblesExt5 = glm::scale(modelMatrixColliderMueblesExt5, glm::vec3(0.1f));
		modelMatrixColliderMueblesExt5 = glm::translate(modelMatrixColliderMueblesExt5, 
						glm::vec3(modelMuebles.getObb().c.x,
						modelMuebles.getObb().c.y,
						modelMuebles.getObb().c.z));
		MueblesExt5Collider.c = glm::vec3(modelMatrixColliderMueblesExt5[3]);
		MueblesExt5Collider.e = modelMuebles.getObb().e * glm::vec3(0.01f);
		addOrUpdateColliders(collidersOBB, "MueblesExt5", MueblesExt5Collider, matrixModelMueblesExt5);

		// Collider de MueblesExt6
		glm::mat4 modelMatrixColliderMueblesExt6= glm::mat4(matrixModelMueblesExt6);
		AbstractModel::OBB MueblesExt6Collider;
		// Set the orientation of collider before doing the scale
		MueblesExt6Collider.u = glm::quat_cast(matrixModelMueblesExt6);
		modelMatrixColliderMueblesExt6 = glm::scale(modelMatrixColliderMueblesExt6, glm::vec3(0.1f));
		modelMatrixColliderMueblesExt6 = glm::translate(modelMatrixColliderMueblesExt6, 
						glm::vec3(modelMuebles.getObb().c.x,
						modelMuebles.getObb().c.y,
						modelMuebles.getObb().c.z));
		MueblesExt6Collider.c = glm::vec3(modelMatrixColliderMueblesExt6[3]);
		MueblesExt6Collider.e = modelMuebles.getObb().e * glm::vec3(0.01f);
		addOrUpdateColliders(collidersOBB, "MueblesExt6", MueblesExt6Collider, matrixModelMueblesExt6);

		// Collider de MueblesExt7
		glm::mat4 modelMatrixColliderMueblesExt7= glm::mat4(matrixModelMueblesExt7);
		AbstractModel::OBB MueblesExt7Collider;
		// Set the orientation of collider before doing the scale
		MueblesExt7Collider.u = glm::quat_cast(matrixModelMueblesExt7);
		modelMatrixColliderMueblesExt7 = glm::scale(modelMatrixColliderMueblesExt7, glm::vec3(0.1f));
		modelMatrixColliderMueblesExt7 = glm::translate(modelMatrixColliderMueblesExt7, 
						glm::vec3(modelMuebles.getObb().c.x,
						modelMuebles.getObb().c.y,
						modelMuebles.getObb().c.z));
		MueblesExt7Collider.c = glm::vec3(modelMatrixColliderMueblesExt7[3]);
		MueblesExt7Collider.e = modelMuebles.getObb().e * glm::vec3(0.01f);
		addOrUpdateColliders(collidersOBB, "MueblesExt7", MueblesExt7Collider, matrixModelMueblesExt7);

		// Collider de MueblesExt8
		glm::mat4 modelMatrixColliderMueblesExt8= glm::mat4(matrixModelMueblesExt8);
		AbstractModel::OBB MueblesExt8Collider;
		// Set the orientation of collider before doing the scale
		MueblesExt8Collider.u = glm::quat_cast(matrixModelMueblesExt8);
		modelMatrixColliderMueblesExt8 = glm::scale(modelMatrixColliderMueblesExt8, glm::vec3(0.1f));
		modelMatrixColliderMueblesExt8 = glm::translate(modelMatrixColliderMueblesExt8, 
						glm::vec3(modelMuebles.getObb().c.x,
						modelMuebles.getObb().c.y,
						modelMuebles.getObb().c.z));
		MueblesExt8Collider.c = glm::vec3(modelMatrixColliderMueblesExt8[3]);
		MueblesExt8Collider.e = modelMuebles.getObb().e * glm::vec3(0.01f);
		addOrUpdateColliders(collidersOBB, "MueblesExt8", MueblesExt8Collider, matrixModelMueblesExt8);
		

		/*******************************************
		 * Render de colliders
		 *******************************************/
		for (std::map<std::string, std::tuple<AbstractModel::OBB, glm::mat4, glm::mat4> >::iterator it =
				collidersOBB.begin(); it != collidersOBB.end(); it++) {
			glm::mat4 matrixCollider = glm::mat4(1.0);
			matrixCollider = glm::translate(matrixCollider, std::get<0>(it->second).c);
			matrixCollider = matrixCollider * glm::mat4(std::get<0>(it->second).u);
			matrixCollider = glm::scale(matrixCollider, std::get<0>(it->second).e * 2.0f);
			boxCollider.setColor(glm::vec4(0.0, 0.0, 0.0, 0.01));
			boxCollider.enableWireMode();
			boxCollider.render(matrixCollider);
		}

		for (std::map<std::string, std::tuple<AbstractModel::SBB, glm::mat4, glm::mat4> >::iterator it =
				collidersSBB.begin(); it != collidersSBB.end(); it++) {
			glm::mat4 matrixCollider = glm::mat4(1.0);
			matrixCollider = glm::translate(matrixCollider, std::get<0>(it->second).c);
			matrixCollider = glm::scale(matrixCollider, glm::vec3(std::get<0>(it->second).ratio * 2.0f));
			sphereCollider.setColor(glm::vec4(1.0, 1.0, 1.0, 1.0));
			sphereCollider.enableWireMode();
			sphereCollider.render(matrixCollider);
		}

		/**********Render de transparencias***************/
		renderAlphaScene();

		/*********************Prueba de colisiones****************************/

		//SBB SBB
		for (std::map<std::string,
			std::tuple<AbstractModel::SBB, glm::mat4, glm::mat4>>::iterator it =
			collidersSBB.begin(); it != collidersSBB.end(); it++) {
			bool isCollision = false;
			for (std::map<std::string,
				std::tuple<AbstractModel::SBB, glm::mat4, glm::mat4>>::iterator jt =
				collidersSBB.begin(); jt != collidersSBB.end(); jt++) {
				if (it != jt && testSphereSphereIntersection(
					std::get<0>(it->second), std::get<0>(jt->second))) {
					std::cout << "Hay collision entre " << it->first <<
						" y el modelo " << jt->first << std::endl;
					isCollision = true;
				}
			}
			addOrUpdateCollisionDetection(collisionDetection, it->first, isCollision);
		}

		//OBB OBB
	

		for (std::map<std::string,
			std::tuple<AbstractModel::OBB, glm::mat4, glm::mat4>>::iterator it =
			collidersOBB.begin(); it != collidersOBB.end(); it++) {
			isColision = false;
			for (std::map<std::string,
				std::tuple<AbstractModel::OBB, glm::mat4, glm::mat4>>::iterator jt =
				collidersOBB.begin(); jt != collidersOBB.end(); jt++) {
				if (it != jt && 
					testOBBOBB(std::get<0>(it->second), std::get<0>(jt->second))) {
					std::cout << "Hay colision entre " << it->first << " y el modelo" <<
						jt->first << std::endl;
					time_before_loop_begins = time(NULL);
					isColision = true;
					for(int i=0; i<=56;i++){
						if(jt->first == chairSets[i]){
						std::cout << "COLISION CON MUEBLE:  " << jt->first << std::endl;
						currentChair = jt->first;
						//Con funcion random
						/*
						if(jt->first == chairSets[v1] && it->first == "mayow"){
							textoNoticia = "Has encontrado la llave. Escapa.";
							llave = true;
						}
						*/
						//De prueba
						if(jt->first == "MueblesExt1" && it->first == "mayow"){
							textoNoticia = "Has encontrado la llave. Escapa.";
							llave = true;
						}

						}						
					}
					if(jt->first == "TiendasSalida" && it->first == "mayow" && llave){
						playerLife = -1;
						alSourceStopv(6, source);
						
					}
					for(int i=0; i<5; i++){
						if(jt->first == spiderSets[i] && it->first == "mayow" && !spiderCollision){
						if(!spiderCollision){
							numCollisionsSpider = 1;
							spiderCollision=true;
							if(spiderCollision2){
								numCollisionsSpider = 2;
							}if(spiderCollision3){
								numCollisionsSpider = 3;
							}if(spiderCollision4){
								numCollisionsSpider = 4;
							}
						}
	
						}
					}
					
					
					
				}
			}
			addOrUpdateCollisionDetection(collisionDetection, it->first, isColision);
		}		

		if(spiderCollision && !isColision){
			if(numCollisionsSpider == 1){
				playerLife = 3;
				spiderCollision2 = true;
			}else if(numCollisionsSpider == 2){
				playerLife = 2;
				spiderCollision3 = true;
			}else if(numCollisionsSpider == 3){
				playerLife = 1;
				spiderCollision4 = true;
			}else if(numCollisionsSpider == 4){
				playerLife = 0;
				alSourceStopv(6, source);
			}
			spiderCollision = false;
		}
		if(playerLife == -1){
			alSourceStopv(6, source);
		}


		if(!playing){
			alSourcePlayv(6, source);
		}
		
		//SBB OBB
		for (std::map<std::string,
			std::tuple<AbstractModel::SBB, glm::mat4, glm::mat4>>::iterator it =
			collidersSBB.begin(); it != collidersSBB.end(); it++) {
			bool isCollision = false;
			for (std::map<std::string,
				std::tuple<AbstractModel::OBB, glm::mat4, glm::mat4>>::iterator jt =
				collidersOBB.begin(); jt != collidersOBB.end(); jt++) {
				if (testSphereOBox(std::get<0>(it->second), std::get<0>(jt->second))) {
					std::cout << "Hay colision del " << it->first << " y el modelo" <<
						jt->first << std::endl;
					isCollision = true;
					addOrUpdateCollisionDetection(collisionDetection, jt->first, true);
				}
			}
			addOrUpdateCollisionDetection(collisionDetection, it->first, isCollision);
		}

		//SBB OBB
		std::map<std::string, bool>::iterator itCollision;
		for (itCollision = collisionDetection.begin(); 
			itCollision != collisionDetection.end(); itCollision++) {
			std::map<std::string, std::tuple<AbstractModel::SBB, 
				glm::mat4, glm::mat4>>::iterator sbbBuscado = 
				collidersSBB.find(itCollision->first);
			std::map<std::string, std::tuple<AbstractModel::OBB,
				glm::mat4, glm::mat4>>::iterator obbBuscado =
				collidersOBB.find(itCollision->first);
			if (sbbBuscado != collidersSBB.end()) {
				if (!itCollision->second) 
					addOrUpdateColliders(collidersSBB, itCollision->first);
			}
			if (obbBuscado != collidersOBB.end()) {
				if (!itCollision->second) 
					addOrUpdateColliders(collidersOBB, itCollision->first);
				else {
					if (itCollision->first.compare("mayow") == 0)
						modelMatrixMayow = std::get<1>(obbBuscado->second);
					if (itCollision->first.compare("dart") == 0)
						modelMatrixDart = std::get<1>(obbBuscado->second);
				}
			}
		}

		glm::mat4 modelMatrixRayMay = glm::mat4(modelMatrixMayow);
		modelMatrixRayMay = glm::translate(modelMatrixRayMay, glm::vec3(0, 1, 0));
		float maxDistanceRay = 10.0;
		glm::vec3 rayDirection = modelMatrixRayMay[2];
		glm::vec3 ori = modelMatrixRayMay[3];
		glm::vec3 rmd = ori + rayDirection * (maxDistanceRay / 2.0f);
		glm::vec3 targetRay = ori + rayDirection * maxDistanceRay;
		modelMatrixRayMay[3] = glm::vec4(rmd, 1.0);
		modelMatrixRayMay = glm::rotate(modelMatrixRayMay, glm::radians(90.0f), 
			glm::vec3(1, 0, 0));
		modelMatrixRayMay = glm::scale(modelMatrixRayMay, 
			glm::vec3(0.05, maxDistanceRay, 0.05));
		rayModel.render(modelMatrixRayMay);

		std::map<std::string, std::tuple<AbstractModel::SBB, glm::mat4, glm::mat4>>::
			iterator itSBB;
		for (itSBB = collidersSBB.begin(); itSBB != collidersSBB.end(); itSBB++) {
			float tRint;
			if (raySphereIntersect(ori, targetRay, rayDirection,
				std::get<0>(itSBB->second), tRint)) {
				std::cout << "Collision del rayo con el modelo " << itSBB->first 
				<< std::endl;
			}
		}
		
		/**********Maquinas de estado*************/
		
		
		
		switch (stateSpider1)
			{
			case 0:
				maxAdvanceSpider = -50.3f;
				stateSpider1 = 1;
				break;
			
			case 1:
				modelMatrixSpider=glm::translate(modelMatrixSpider, glm::vec3(0.0,0.0,advanceCountSpider));
				advanceCountSpider-=avanceSpider;
				if(advanceCountSpider<maxAdvanceSpider){
					advanceCountSpider = 0.0;
					stateSpider1=2;	
				}
				break;

			case 2:
				//Case 2 es para definir cuando esta dando vuelta
				modelMatrixSpider = glm::translate(modelMatrixSpider, glm::vec3(0,0,0.025));
				//Checamos que el Spider se pueda rotar en base de y, utilizando la variable rotSpider
				modelMatrixSpider = glm::rotate(modelMatrixSpider,glm::radians(rotSpider),glm::vec3(0.0f, 1.0f, 0.0f));
				rotCountSpider+=rotSpider;
				//Limitamos la rotacion
				if(rotCountSpider>180.0){
					//Al terminar de rotar, se regresa el valor a 0 para poder realizar el giro nuevamente
					rotCountSpider = 0;
					stateSpider1 = 0;

				}
				break;

			default:
				break;
			}
		
		switch (stateSpider2)
			{
			case 0:
				maxAdvanceSpider2 = -50.3f;
				stateSpider2 = 1;
				break;
			
			case 1:
				modelMatrixSpider2=glm::translate(modelMatrixSpider2, glm::vec3(0.0,0.0,advanceCountSpider2));
				advanceCountSpider2-=avanceSpider2;
				if(advanceCountSpider2<maxAdvanceSpider2){
					advanceCountSpider2 = 0.0;
					animationSpiderIndex2 = 1;
					stateSpider2=2;	
				}
				break;

			case 2:
				//modelMatrixSpider = glm::translate(modelMatrixSpider, glm::vec3(0,0,0.025));
				//Checamos que el Spider se pueda rotar en base de y, utilizando la variable rotSpider
				modelMatrixSpider2 = glm::rotate(modelMatrixSpider2,glm::radians(rotSpider2),glm::vec3(0.0f, 1.0f, 0.0f));
				rotCountSpider2+=rotSpider2;
				//Limitamos la rotacion
				if(rotCountSpider2>180.0){
					//Al terminar de rotar, se regresa el valor a 0 para poder realizar el giro nuevamente
					rotCountSpider2 = 0;
					stateSpider2 = 0;

				}
				break;

			default:
				break;
			}

			switch (stateSpider3)
			{
			case 0:
				maxAdvanceSpider3 = -70.3f;
				stateSpider3 = 1;
				break;
			
			case 1:
				modelMatrixSpider3=glm::translate(modelMatrixSpider3, glm::vec3(0.0,0.0,advanceCountSpider3));
				advanceCountSpider3-=avanceSpider3;
				if(advanceCountSpider3<maxAdvanceSpider3){
					advanceCountSpider3 = 0.0;
					stateSpider3=2;	
				}
				break;

			case 2:
				modelMatrixSpider3 = glm::translate(modelMatrixSpider3, glm::vec3(0,0,0.045));
				//Checamos que el Spider se pueda rotar en base de y, utilizando la variable rotSpider
				modelMatrixSpider3 = glm::rotate(modelMatrixSpider3,glm::radians(rotSpider3),glm::vec3(0.0f, 1.0f, 0.0f));
				rotCountSpider3+=rotSpider3;
				//Limitamos la rotacion
				if(rotCountSpider3>180.0){
					//Al terminar de rotar, se regresa el valor a 0 para poder realizar el giro nuevamente
					rotCountSpider3 = 0;
					stateSpider3 = 0;

				}
				break;

			default:
				break;
			}

			switch (stateSpider4)
			{
			case 0:
				maxAdvanceSpider4 = -50.3f;
				stateSpider4 = 1;
				break;
			
			case 1:
				modelMatrixSpider4=glm::translate(modelMatrixSpider4, glm::vec3(0.0,0.0,advanceCountSpider4));
				advanceCountSpider4-=avanceSpider4;
				if(advanceCountSpider4<maxAdvanceSpider4){
					advanceCountSpider4 = 0.0;
					
					stateSpider4=2;	
				}
				break;

			case 2:
				//modelMatrixSpider = glm::translate(modelMatrixSpider, glm::vec3(0,0,0.025));
				//Checamos que el Spider se pueda rotar en base de y, utilizando la variable rotSpider
				modelMatrixSpider4 = glm::rotate(modelMatrixSpider4,glm::radians(rotSpider4),glm::vec3(0.0f, 1.0f, 0.0f));
				rotCountSpider4+=rotSpider4;
				//Limitamos la rotacion
				if(rotCountSpider4>180.0){
					//Al terminar de rotar, se regresa el valor a 0 para poder realizar el giro nuevamente
					rotCountSpider4 = 0;
					stateSpider4 = 0;

				}
				break;

			default:
				break;
			}
			

		// Constantes de animaciones
		rotHelHelY += 0.5;
		rotHelHelBack += 0.5;
		animationMayowIndex = 3;
		animationSpiderIndex = 1;

		glfwSwapBuffers(window);

		/****************************+
		 * Open AL sound data
		 */
		source0Pos[0] = matrixModelTelevision1[3].x;
		source0Pos[1] = matrixModelTelevision1[3].y;
		source0Pos[2] = matrixModelTelevision1[3].z;
		alSourcefv(source[0], AL_POSITION, source0Pos);

		source1Pos[0] = matrixModelTelevision2[3].x;
		source1Pos[1] = matrixModelTelevision2[3].y;
		source1Pos[2] = matrixModelTelevision2[3].z;
		alSourcefv(source[1], AL_POSITION, source1Pos);
		
		source2Pos[0] = matrixModelTelevision3[3].x;
		source2Pos[1] = matrixModelTelevision3[3].y;
		source2Pos[2] = matrixModelTelevision3[3].z;
		alSourcefv(source[2], AL_POSITION, source2Pos);
//
		source3Pos[0] = matrixModelTelevision1Ext[3].x;
		source3Pos[1] = matrixModelTelevision1Ext[3].y;
		source3Pos[2] = matrixModelTelevision1Ext[3].z;
		alSourcefv(source[3], AL_POSITION, source3Pos);

		source4Pos[0] = matrixModelTelevision2Ext[3].x;
		source4Pos[1] = matrixModelTelevision2Ext[3].y;
		source4Pos[2] = matrixModelTelevision2Ext[3].z;
		alSourcefv(source[4], AL_POSITION, source4Pos);

		source5Pos[0] = matrixModelTelevision3Ext[3].x;
		source5Pos[1] = matrixModelTelevision3Ext[3].y;
		source5Pos[2] = matrixModelTelevision3Ext[3].z;
		alSourcefv(source[5], AL_POSITION, source5Pos);
		

		// Listener for the Third person camera
		listenerPos[0] = modelMatrixMayow[3].x;
		listenerPos[1] = modelMatrixMayow[3].y;
		listenerPos[2] = modelMatrixMayow[3].z;
		alListenerfv(AL_POSITION, listenerPos);

		glm::vec3 upModel = glm::normalize(modelMatrixMayow[1]);
		glm::vec3 frontModel = glm::normalize(modelMatrixMayow[2]);

		listenerOri[0] = frontModel.x;
		listenerOri[1] = frontModel.y;
		listenerOri[2] = frontModel.z;
		listenerOri[3] = upModel.x;
		listenerOri[4] = upModel.y;
		listenerOri[5] = upModel.z;
		
		alListenerfv(AL_ORIENTATION, listenerOri);

		for(unsigned int i = 0; i < sourcesPlay.size(); i++){
			if(sourcesPlay[i]){
				sourcesPlay[i] = false;
				alSourcePlay(source[i]);
			}
		}
	}
}

int main(int argc, char **argv) {
	init(800, 700, "Window GLFW", false);
	applicationLoop();
	destroy();
	return 1;
}