//https://github.com/the-cat1/iample
//版本:        1.0.1
//项目更新时间: 2022年8月7日 19点53分
//编译环境:     tcc version 0.9.27 (x86_64 Windows)

#include <stdio.h>
#include <stdlib.h>
#define REGISTER_LEN 16 /*寄存器长度*/

#define ERROR_MAG_1 "Error(1)\n\t缺少输入参数!(需要文件名)\n"
#define ERROR_MAG_2 "Error(2)\n\t文件\"%s\"读取错误!\n"

int _Register[REGISTER_LEN] = {0};               //寄存器
int regPos = 0;                                  //当前指向的寄存器
int jumpPos = 0;                                 //上一次记录的位置


int main(int argc, char const *argv[])
{
    //判断是否有输入文件
    if (argc < 2){
        printf(ERROR_MAG_1);
        return -1;
    }
    
    //读取文件
    FILE * fp;
    if ((fp = fopen(argv[1], "r")) == NULL){     //如果文件不存在
        printf(ERROR_MAG_2, argv[1]);
        return -2;
    }

    fseek(fp, 0L, SEEK_END);                     //计算文件长度
    int len = (int)ftell(fp) + 1;                //
    char * script = (char *)calloc(len, sizeof(char));
    rewind(fp);                                  //读取文件
    fread(script, sizeof(char), len, fp);        //
    fclose(fp);                                  //关闭文件

    for (int i = 0; i < len; i++){
        switch (script[i])                       //判断命令
        {
        /***********寄存器操作**********/
        case '+':
            //当前寄存器加一
            _Register[regPos]++;
            break;

        case '-':
            //当前寄存器减一
            _Register[regPos]--;
            break;

        case '>':
            //下一个寄存器
            if (regPos < REGISTER_LEN){
                regPos++;
            }
            break;

        case '<':
            //上一个寄存器
            if (regPos > 0){
                regPos--;
            }
            break;

        case '{':
            //把当前寄存器的数值复制到第一个特殊寄存器
            _Register[REGISTER_LEN - 2] = _Register[regPos];
            break;

        case '}':
            //把当前寄存器的数值复制到第二个特殊寄存器
            _Register[REGISTER_LEN - 1] = _Register[regPos];
            break;
        
        /************跳转************/
        case '|':
            //记录当前位置
            jumpPos = i;
            break;

        case '[':
            //向后跳转
            for (; i < len; i++){
                if (script[i] == '|'){
                    jumpPos = i;
                    break;
                }
            }
            break;

        case ']':
            //向前跳转(跳转到上一个位置)
            i = jumpPos;
            break;

        /************重置************/
        case '^':
            //重置regPos
            regPos = 0;
            break;

        case '=':
            //重置当前寄存器
            _Register[regPos] = 0;
            break;

        /************判断************/
        case '?':
            //if判断
            i++;                                 //跳过下一个字符
            int isJump = 0;                      //是否跳转(0:否 1:是)
            switch (script[i])                   //判断符号类型
            {
            case '=':
                if (_Register[REGISTER_LEN - 2] == _Register[REGISTER_LEN - 1]){
                    isJump = 1;
                }
                break;

            case '<':
                if (_Register[REGISTER_LEN - 2] < _Register[REGISTER_LEN - 1]){
                    isJump = 1;
                }
                break;

            case '>':
                if (_Register[REGISTER_LEN - 2] > _Register[REGISTER_LEN - 1]){
                    isJump = 1;
                }
                break;
            
            default:
                break;
            }
            if (isJump != 0){                    //是否需要跳转
                i++;                             //跳过方向指向符号
                if (script[i] == '{'){
                    //向左跳转
                    for (; i > 0; i--){
                        if (script[i] == '|'){   //寻找“|”
                            jumpPos = i;
                            break;
                        }
                    }
                }else if (script[i] = '}'){
                    //向右跳转
                    for (; i < len; i++){
                        if (script[i] == '|'){   //寻找“|”
                            jumpPos = i;
                            break;
                        }
                    }
                }
            }
            
            break;

        /***********输入输出***********/
        case '.':
            //把寄存器输出到屏幕
            putchar(_Register[regPos]);
            break;

        case ',':
            //从键盘输入到寄存器
            _Register[regPos] = getchar();
            break;
        
        default:
            //特殊字符(无视)
            break;
        }
    }

    return 0;
}
