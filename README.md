# OpenGL
This is a basic graphic pipeline which contains two tests :
1. Color Test - It can generate the color specified for the current size of the screen with the given R G B values.
2. Texture Generation Test - It can generate any specified texture( a tiger image texture twice for this case )

For the GUI it uses the library imgui v1.60
and for Reading the texture I have used stb_image
for the transformation and other mathematics related stuff I have used glm

If you want to render your own texture then just download this project and go to the src/test/TestTexture2D.cpp and on the 40th line change this:  m_Texture = std::make_unique<Texture>("res/texture/tiger.png");
and specify the path of the texture you want ot load instead of the given texture related to the solution directory.
