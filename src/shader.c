#include <stdio.h>
#include <string.h>
#include <shader.h>
#include <glew.h>

static FILE* _shd_f;  // .glsl file buffer

/// @brief read in shader source code from a glsl file
/// @param shd_buf string to store read in source code
/// @return shader type of read in shader
/// @note 1. _shd_f must be OPENED before calling this!
/// @note 2. DON'T read other shaders without finishing reading current one!
static int read_shd_src(char* shd_buf)
{
    char tag[16], tmp[64];
    int shd_t = 0, shd_src_len = 0, cnt;
    // identify current tag
    while (fgets(tag, 16 * sizeof(char), _shd_f)) {
        if (!strcmp(tag, "<vtx>\n")) {
            strcpy(tag, "</vtx>\n");
            shd_t = GL_VERTEX_SHADER;
            break;
        } else if (!strcmp(tag, "<frag>\n")) {
            strcpy(tag, "</frag>\n");
            shd_t = GL_FRAGMENT_SHADER;
            break;
        } else if (!strcmp(tag,"<geo>\n")) {
            strcpy(tag, "</geo>\n");
            shd_t = GL_GEOMETRY_SHADER;
            break;
        }
    }
    // read file content line by line
    while (strcmp(fgets(tmp, 64 * sizeof(char), _shd_f), tag)) {
        printf("%s", tmp);
        cnt = 0;
        while (tmp[cnt] != '\0') {
            shd_buf[shd_src_len++] = tmp[cnt++];
        }
    }
    return shd_t;
}

void make_shd(unsigned int prog_i, char* shd_f_name)
{
    _shd_f = fopen(shd_f_name, "r");  // open shader source file
    char shd_buf[2048];               // string buffer to store shader source code
    const char* tmp = shd_buf;        // pointer to shader buffer
    // iteratively compile each shader in shd_f_name.glsl
    int shd_t;
    while ((shd_t = read_shd_src(shd_buf))) {
        int shd_i = glCreateShader(shd_t);
        glShaderSource(shd_i, 1, &tmp, (const int*)0);
        glCompileShader(shd_i);
        printf("%s", tmp);
        // show compile information
        int compile_status = GL_FALSE;
        glGetShaderiv(shd_i, GL_COMPILE_STATUS, &compile_status);
        if (compile_status == GL_FALSE) {
            int compile_info_len;
            glGetShaderiv(shd_i, GL_INFO_LOG_LENGTH, &compile_info_len);
            if (compile_info_len) {
                char* compile_info = (char*)malloc(compile_info_len * sizeof(char));
                glGetShaderInfoLog(shd_i, compile_info_len, &compile_info_len, compile_info);
                printf("%s\n", compile_info);
				free(compile_info);
            }
        }
        glAttachShader(prog_i, shd_i);
    }
    glLinkProgram(prog_i);

    fclose(_shd_f);
}