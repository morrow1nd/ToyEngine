lemon -l -Tlempar.c toy_shader_parser.y
move /Y toy_shader_parser.c ..\..\..\Source\ToyEngine\Graphics\ToyShaderParser\toy_shader_parser.cpp
move /Y toy_shader_parser.h ..\..\..\Include\ToyEngine\Graphics\ToyShaderParser\toy_shader_token_id.h
lemon -Tlempar.c toy_shader_parser.y
move /Y toy_shader_parser.c ..\..\..\Source\ToyEngine\Graphics\ToyShaderParser\toy_shader_parser_with_#line.cpp

move /Y toy_shader_parser.out ..\..\..\Source\ToyEngine\Graphics\ToyShaderParser\toy_shader_parser.out
del toy_shader_parser.h