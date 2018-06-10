// Toy Engine Shader Language Lemon Grammar Rules


%parse_failure {
    generator->ParseFailure();
}

%stack_overflow {
    generator->StackOverflow();
}

%parse_accept {
    generator->ParseAccept();
}

%syntax_error {
    generator->SyntaxError();
}


%include {
    #include <cassert>
    #include "TRL/TRLSL/Token.h"
    #include "TRL/TRLSL/TRLSLGenerator.h"
}

%name TrlSLParser_  // Functions in generated code all begins with this string.
%token_prefix TRLSL_T_
%token_type {TRL::Token*}

%extra_context { TRL::TRLSLGenerator* generator }


%start_symbol translation_unit


variable_type ::= .

material_type ::= BOOL.
material_type ::= COLOR.
material_type ::= FLOAT_RANGE LS NUMBER COMMA NUMBER RS.
material_type ::= INT_RANGE LS NUMBER COMMA NUMBER RS.
material_type ::= TEXTURE_2D.
material_type ::= TEXTURE_CUBE.
material_type ::= TEXTURE_3D.
material_type ::= TEXTURE_2DARRAY.
material_type ::= VECTOR.




initalize_list ::= LB  RB.

propertie ::= variable_type IDENTIFIER LS CONSTANT_STRING material_type RS ASSIGN initalize_list.

propertie_list ::= propertie.
propertie_list ::= propertie_list propertie.

properties_block ::= PROPERTIES LB propertie_list RB.

pass ::= PASS CONSTANT_STRING LB GLSL_VERTEX LB LITERAL_CONTENT RB GLSL_FRAGEMENT LB LITERAL_CONTENT RB RB.
pass ::= PASS CONSTANT_STRING LB TRLSL_VERTEX LB LITERAL_CONTENT RB TRLSL_FRAMEMENT LB LITERAL_CONTENT RB RB.

pass_list ::= pass.
pass_list ::= pass_list pass.

subshader ::= SUB_SHADER CONSTANT_STRING LB pass_list RB.

subshader_list ::= subshader.
subshader_list ::= subshader_list subshader.

fallback ::= FALLBACK CONSTANT_STRING.

translation_unit ::= SHADER CONSTANT_STRING LB properties_block subshader_list fallback RB.
