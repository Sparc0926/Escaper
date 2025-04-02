<vtx>
#version 330 core

void main()
{
	gl_Position = vec4(0.0f, 0.0f, 0.0f, 1.0f);
}
</vtx>

<frag>
#version 330 core

out vec4 FragColor;

void main()
{
	FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}
</frag>