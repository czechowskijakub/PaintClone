#include "DrawTool.hpp"

class Spray : DrawTool {
private:
	float fSize = .02f;
	float fXPos = 0;
	float fYPos = 0;
	std::string sName = "Pencil";
	GLuint VBO, VAO;
	GLuint drawShader = 0;
public:
	Spray();

	std::string sGetName() const override;

	float fGetSize() const override;
	float fGetXPos() const override;
	float fGetYPos() const override;

	void setSize(float) override;
	void setXPos(float) override;
	void setYPos(float) override;

	void updateCoords(float, float, float) override;

	void draw(GLuint) override;
};
