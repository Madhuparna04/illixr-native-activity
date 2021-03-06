#include <EGL/egl.h>

static const char* const basicVertexShader =
        "#version 150;\n"
        "in vec3 vertexPosition;\n"
        "in vec2 vertexUV;\n"
        "out vec2 vUV;\n"
        "out gl_PerVertex { vec4 gl_Position; };\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4( vertexPosition, 1.0 );\n"
        "   vUV = vertexUV;\n"
        "}\n";

static const char* const basicFragmentShader =
        "#version 150;\n"
        "uniform highp sampler2DArray Texture;\n"
        "in vec2 vUV;\n"
        "out lowp vec4 outcolor;\n"
        "void main()\n"
        "{\n"
        "   outcolor = vec4(vUV.x, vUV.y, 1.0, 1.0);\n"
        //"   outcolor = vec4(0.0,0.0,0.0, 1.0);\n"
        "     outcolor = texture(Texture, vec3(vUV, 0));\n"
        "}\n";
