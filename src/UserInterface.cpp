#include "UserInterface.h"
#include "Windows.h"


extern int gWidth, gHeight;
void TW_CALL CallbackLoad(void *clientData);
string loadPath();
void beginLoad(string path);

// Global static pointer used to ensure a single instance of the class.
CUserInterface * CUserInterface::mInterface = NULL;

/**
* Creates an instance of the class
*
* @return the instance of this class
*/
CUserInterface * CUserInterface::Instance()
{
	if (!mInterface)   // Only allow one instance of class to be generated.
		mInterface = new CUserInterface();

	return mInterface;
}

CUserInterface::CUserInterface()
{
	mUserInterface = TwNewBar("Model");
	m_currentDeploy = GL_BEGIN_GL_END;
	m_cameraType = PERSPECTIVE;
	m_shadowType = FLAT;
	TwDefine("Model refresh = '0.0001f'");
	TwDefine("Model resizable = false");
	TwDefine("Model fontresizable = false");
	TwDefine("Model movable = false");
	TwDefine("Model position = '20 20'");
	TwDefine("Model size = '220 320'");

	mModelTranslation[0] = 0.0f;
	mModelTranslation[1] = 0.0f;
	mModelTranslation[2] = 0.0f;

	mModelScale[0] = 1.0f;
	mModelScale[1] = 1.0f;
	mModelScale[2] = 1.0f;

	mModelRotation[0] = 0.0f;
	mModelRotation[1] = 0.0f;
	mModelRotation[2] = 0.0f;
	mModelRotation[3] = 1.0f;

	mModelSelect = 2;
	backFace = true;

	TwEnumVal DeployType[] = { { GL_BEGIN_GL_END, "Gl Begin / Gl End" },{ DISPLAY_LIST, "Display List" },{ VERTEX_POINTER, "Vertex Pointer" },{ VBO, "VBO" } };
	TwType DeployTwType = TwDefineEnum("DeployType", DeployType, 4);

	TwEnumVal CameraType[] = { { PERSPECTIVE,"Perspective Camera" },{ ORTHO, "Orthographic_Camera" } };
	TwType CameraTwType = TwDefineEnum("CameraType", CameraType, 2);

	TwEnumVal ShadowType[] = { { FLAT,"Flat" },{ SMOOTH, "Smoth" }};
	TwType ShadowTwType = TwDefineEnum("ShadowType", ShadowType, 2);


	TwAddVarRW(mUserInterface, "Deploy", DeployTwType, &m_currentDeploy, NULL);

	TwAddSeparator(mUserInterface, "", NULL);
	TwAddVarRW(mUserInterface, "Camera", CameraTwType, &m_cameraType, NULL);

	TwAddSeparator(mUserInterface, "", NULL);
	TwAddVarRW(mUserInterface, "Shadow", ShadowTwType, &m_shadowType, NULL);

	TwAddSeparator(mUserInterface, "", NULL);
	TwAddVarRW(mUserInterface, "Back Face", TW_TYPE_BOOL8, &backFace, NULL);

	TwAddSeparator(mUserInterface, "", NULL);
	TwAddVarRW(mUserInterface, "Modelo", TW_TYPE_INT32, &mModelSelect, "min=2");

	TwAddSeparator(mUserInterface, "", NULL);
	TwAddVarRW(mUserInterface, "Translation X", TW_TYPE_FLOAT, &mModelTranslation[0], " group='Model' step=0.01 ");
	TwAddVarRW(mUserInterface, "Translation Y", TW_TYPE_FLOAT, &mModelTranslation[1], " group='Model' step=0.01 ");
	TwAddVarRW(mUserInterface, "Translation Z", TW_TYPE_FLOAT, &mModelTranslation[2], " group='Model' step=0.01 ");

	TwAddSeparator(mUserInterface, "", "group='Model'");
	TwAddVarRW(mUserInterface, "Scale X", TW_TYPE_FLOAT, &mModelScale[0], " group='Model' step=0.01 ");
	TwAddVarRW(mUserInterface, "Scale Y", TW_TYPE_FLOAT, &mModelScale[1], " group='Model' step=0.01 ");
	TwAddVarRW(mUserInterface, "Scale Z", TW_TYPE_FLOAT, &mModelScale[2], " group='Model' step=0.01 ");
	TwAddVarRW(mUserInterface, "Scale All", TW_TYPE_FLOAT, &mScaleAll, " group='Model' step=0.01 ");

	
	TwAddSeparator(mUserInterface, "", "group='Model'");
	TwAddVarRW(mUserInterface, "Rotation Quad", TW_TYPE_QUAT4F, &mModelRotation, "group = 'Model'");

	TwAddSeparator(mUserInterface, "", "group='Model'");
	TwAddVarRW(mUserInterface, "Model Visible", TW_TYPE_BOOL8, &mModelVisible, "group='Model'");
	TwAddVarRW(mUserInterface, "Model Color", TW_TYPE_COLOR3F, &mModelColor, "group='Model'");

	TwAddSeparator(mUserInterface, "", "group='Model'");
	TwAddVarRW(mUserInterface, "Wire Visible", TW_TYPE_BOOL8, &mWireVisible, "group='Model'");
	TwAddVarRW(mUserInterface, "Wire Color", TW_TYPE_COLOR3F, &mWireColor, "group='Model'");

	TwAddSeparator(mUserInterface, "", "group='Model'");
	TwAddVarRW(mUserInterface, "Points Visible", TW_TYPE_BOOL8, &mPointsVisible, "group='Model'");
	TwAddVarRW(mUserInterface, "Points Color", TW_TYPE_COLOR3F, &mPointsColor, "group='Model'");

	TwAddSeparator(mUserInterface, "", "group='Model'");
	TwAddVarRW(mUserInterface, "Faces Normals Visible", TW_TYPE_BOOL8, &mNormalsVisible, "group='Model'");
	TwAddVarRW(mUserInterface, "Faces Normals Color", TW_TYPE_COLOR3F, &mNormalsColor, "group='Model'");

	TwAddSeparator(mUserInterface, "", "group='Model'");
	TwAddVarRW(mUserInterface, "Vertex Normals Visible", TW_TYPE_BOOL8, &mVertexNormalsVisible, "group='Model'");
	TwAddVarRW(mUserInterface, "Vertex Normals Color", TW_TYPE_COLOR3F, &mVertexNormalsColor, "group='Model'");

	TwAddSeparator(mUserInterface, "", NULL);
	TwAddVarRW(mUserInterface, "Light 1 Visible", TW_TYPE_BOOL8, &lOn[0], "group='light'");
	TwAddVarRW(mUserInterface, "Light 1 Position X", TW_TYPE_FLOAT, &lPosition[0].x, "group='light'");
	TwAddVarRW(mUserInterface, "Light 1 Position Y", TW_TYPE_FLOAT, &lPosition[0].y, "group='light'");
	TwAddVarRW(mUserInterface, "Light 1 Position Z", TW_TYPE_FLOAT, &lPosition[0].z, "group='light'");
	TwAddVarRW(mUserInterface, "Light 1 Ambient Color", TW_TYPE_COLOR3F, &lAmbientColor[0], "group='light'");
	TwAddVarRW(mUserInterface, "Light 1 Specular Color", TW_TYPE_COLOR3F, &lSpecularColor[0], "group='light'");
	TwAddVarRW(mUserInterface, "Light 1 Difuse Color", TW_TYPE_COLOR3F, &lDifuseColor[0], "group='light'");
	
	TwAddSeparator(mUserInterface, "", "group='light'");
	TwAddVarRW(mUserInterface, "Light 2 Visible", TW_TYPE_BOOL8, &lOn[1], "group='light'");
	TwAddVarRW(mUserInterface, "Light 2 Position X", TW_TYPE_FLOAT, &lPosition[1].x, "group='light'");
	TwAddVarRW(mUserInterface, "Light 2 Position Y", TW_TYPE_FLOAT, &lPosition[1].y, "group='light'");
	TwAddVarRW(mUserInterface, "Light 2 Position Z", TW_TYPE_FLOAT, &lPosition[1].z, "group='light'");
	TwAddVarRW(mUserInterface, "Light 2 Ambient Color", TW_TYPE_COLOR3F, &lAmbientColor[1], "group='light'");
	TwAddVarRW(mUserInterface, "Light 2 Specular Color", TW_TYPE_COLOR3F, &lSpecularColor[1], "group='light'");
	TwAddVarRW(mUserInterface, "Light 2 Difuse Color", TW_TYPE_COLOR3F, &lDifuseColor[1], "group='light'");

	TwAddSeparator(mUserInterface, "", NULL);
	TwAddVarRW(mUserInterface, "Bonding Visible", TW_TYPE_BOOL8, &mBondingVisible, "group='Bonding Box'");
	TwAddVarRW(mUserInterface, "Bonding Color", TW_TYPE_COLOR3F, &mBondingColor, "group='Bonding Box'");

	TwAddSeparator(mUserInterface, "", NULL);
	TwAddButton(mUserInterface, "Load", CallbackLoad, NULL, NULL);
}

void TW_CALL CallbackLoad(void *clientData)
{
	string path = loadPath();
	if (path != "")
		beginLoad(path);
}

CUserInterface::~CUserInterface()
{
}

void CUserInterface::reshape()
{
	TwWindowSize(gWidth, gHeight);
}

void CUserInterface::show()
{
	TwDefine("Figure visible = true");
}

void CUserInterface::hide()
{
	TwDefine("Figure visible = false");
}

void CUserInterface::setModelTranslation(glm::vec3 modelTranslation)
{
	mModelTranslation[0] = modelTranslation[0];
	mModelTranslation[1] = modelTranslation[1];
	mModelTranslation[2] = modelTranslation[2];
}

void CUserInterface::setModelScale(glm::vec3 modelScale)
{
	mModelScale[0] = modelScale[0];
	mModelScale[1] = modelScale[1];
	mModelScale[2] = modelScale[2];
}
void CUserInterface::setModelRotation(glm::vec4  modelRotation) {

	mModelRotation[0] = modelRotation[0];
	mModelRotation[1] = modelRotation[1];
	mModelRotation[2] = modelRotation[2];
	mModelRotation[3] = modelRotation[3];
}

void CUserInterface::setBondingColor(glm::vec3 Color) {

	mBondingColor[0] = Color[0];
	mBondingColor[1] = Color[1];
	mBondingColor[2] = Color[2];
}

void CUserInterface::setModelColor(glm::vec3 Color) {

	mModelColor[0] = Color[0];
	mModelColor[1] = Color[1];
	mModelColor[2] = Color[2];
}

void CUserInterface::setWireColor(glm::vec3 Color) {

	mWireColor[0] = Color[0];
	mWireColor[1] = Color[1];
	mWireColor[2] = Color[2];
}

void CUserInterface::setPointsColor(glm::vec3 Color) {

	mPointsColor[0] = Color[0];
	mPointsColor[1] = Color[1];
	mPointsColor[2] = Color[2];
}

void CUserInterface::setNormalsColor(glm::vec3 Color) {

	mNormalsColor[0] = Color[0];
	mNormalsColor[1] = Color[1];
	mNormalsColor[2] = Color[2];
}

void CUserInterface::setVertexNormalsColor(glm::vec3 Color) {

	mVertexNormalsColor[0] = Color[0];
	mVertexNormalsColor[1] = Color[1];
	mVertexNormalsColor[2] = Color[2];
}

void CUserInterface::setScaleAll(float v) {

	mScaleAll = v;

}

void CUserInterface::setBondingVisible(bool v) {

	mBondingVisible = v;
}

void CUserInterface::setLOn(int a ,bool v) {

	lOn[a] = v;
}

void CUserInterface::setPointsVisible(bool v) {

	mPointsVisible = v;
}

void CUserInterface::setWireVisible(bool v) {

	mWireVisible = v;
}

void CUserInterface::setNormalsVisible(bool v) {

	mNormalsVisible = v;
}

void CUserInterface::setVertexNormalsVisible(bool v) {

	mVertexNormalsVisible = v;
}

void CUserInterface::setModelVisible(bool v) {

	mModelVisible = v;
}

void CUserInterface::setSelectModel(int v) {

	mModelSelect = v;
}


glm::vec3 CUserInterface::getModelTranslation()
{
	return mModelTranslation;
}

glm::vec3 CUserInterface::getModelScale()
{
	return mModelScale;
}

glm::vec4 CUserInterface::getModelRotation()
{
	return mModelRotation;
}

glm::vec3 CUserInterface::getBondingColor()
{
	return mBondingColor;
}

glm::vec3 CUserInterface::getModelColor()
{
	return mModelColor;
}

glm::vec3 CUserInterface::getWireColor()
{
	return mWireColor;
}

glm::vec3 CUserInterface::getPointsColor()
{
	return mPointsColor;
}

glm::vec3 CUserInterface::getNormalsColor()
{
	return mNormalsColor;
}

glm::vec3 CUserInterface::getVertexNormalsColor()
{
	return mVertexNormalsColor;
}

bool CUserInterface::getBondingVisible() {

	return mBondingVisible;
}

bool CUserInterface::getPointsVisible() {

	return mPointsVisible;
}

bool CUserInterface::getWireVisible() {

	return mWireVisible;
}

bool CUserInterface::getNormalsVisible() {

	return mNormalsVisible;
}

bool CUserInterface::getVertexNormalsVisible() {

	return mVertexNormalsVisible;
}

bool CUserInterface::getModelVisible() {

	return mModelVisible;
}

int CUserInterface::getSelectModel() {

	return mModelSelect;
}

float CUserInterface::getScaleAll() {

	return mScaleAll;
}

string loadPath()
{
	OPENFILENAME ofn;
	char fileName[MAX_PATH] = "";
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = NULL;
	ofn.lpstrFilter = "OBJ Files(.obj)\0*.obj\0OFF Files(.off)\0*.off";
	ofn.lpstrFile = fileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = "";
	string fileNameStr;
	if (GetOpenFileName(&ofn))
		fileNameStr = fileName;
	return fileNameStr;
}

string CUserInterface::getDeployType() {
	if (m_currentDeploy == GL_BEGIN_GL_END) return "glBE";
	if (m_currentDeploy == DISPLAY_LIST) return "DL";
	if (m_currentDeploy == VERTEX_POINTER) return "VP";
	if (m_currentDeploy == VBO) return "VBO";
	return NULL;
}

string CUserInterface::getCameraType() {
	if (m_cameraType == PERSPECTIVE) return "perspective";
	if (m_cameraType == ORTHO) return "ortho";
	return NULL;
}

void CUserInterface::setLAmbientColor(glm::vec3 Color,int p) {

	lAmbientColor[p] = Color;

}

void CUserInterface::setLSpecularColor(glm::vec3 Color,int p) {

	lSpecularColor[p] = Color;

}

void CUserInterface::setLDifuseColor(glm::vec3 Color,int p) {

	lDifuseColor[p] = Color;

}

void CUserInterface::setLPosition(glm::vec3 position,int p) {

	lPosition[p] = position;

}

glm::vec3 CUserInterface::getLAmbientColor(int p) {

	return lAmbientColor[p];

}

glm::vec3 CUserInterface::getLSpecularColor(int p) {

	return lSpecularColor[p];

}

glm::vec3 CUserInterface::getLDifuseColor(int p) {

	return lDifuseColor[p];

}

glm::vec3 CUserInterface::getLPosition(int p) {

	return lPosition[p];

}

bool CUserInterface::getLOn(int a ) {

	return lOn[a];
}

string CUserInterface::getShadowType() {

	if (m_shadowType == PERSPECTIVE) return "smoth";
	if (m_shadowType == ORTHO) return "flat";
}

bool CUserInterface::getBackFace() {

	return backFace;
}