#ifndef SHADER_H
#define SHADER_H

// <vtx></vtx>     for vertex shader
// <frag></frag>   for fragment shader
// <geo></geo>     for geometry shader
// <tes></tes>     for tessellation evaluation shader
// <comp></comp>   for compute shader

/// @brief make a .glsl file into a shader program
/// @param prog_i index of shader progeam
/// @param shader_f name of .glsl file
/// @note shd_f_name.glsl should end with a blank line!
void make_shd(unsigned int prog_i, char* shd_f_name);

#endif//SHADER_H