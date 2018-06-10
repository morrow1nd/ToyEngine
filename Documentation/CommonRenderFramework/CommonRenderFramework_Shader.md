# Common Render Framework - Shader


## Shader File


Struct:

```
Shader "name" { [Properties] Subshaders [Fallback] [CustomEditor] }
```


Syntax Example:

```
Shader "MyCustomShader/Ulint"
{
    Properties
    {
        fixed4      _MainColor ("Main Color", Color) = (1, 0.5, 0.5, 1)
        int4        _SomeThing ("SomeThing", Raw) = (1, 2, 3, 4)
    }

    // Define one subshader
    SubShader
    {
        // a single pass in our subshader
        Pass
        {

        }
    }

    // Another subshader, you can specify a name for this subShader
    SubShader "name"
    {
        Pass "name"
        {
            glsl.vertex
            {
                in vec4 _MainColor;
                in vec4i _SomeThing;

                out vec4 Color;

                void main()
                {
                    gl_Position = vec4(CRF_pos, 1.0);
                    Color = _MainColor;
                }
            }
            glsl.fragement
            {
                in vec4 Color;
                out vec4 FragColor;
                void main()
                {
                    FragColor = Color;
                }
            }
        }

        Pass
        {

        }
    }


}




```

