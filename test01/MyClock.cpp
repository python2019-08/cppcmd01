#include "MyClock.h"


#include <iostream>
#include <thread>
#include <future>
#include <chrono>
#include <cstdlib> // ����system������ͷ�ļ� 

#pragma comment(lib, "Winmm.lib")

#ifdef  OS_WINDOWS
#include <windows.h>  
#include <mmdeviceapi.h>  
#endif
#include <iostream>  

// �滻Ϊ��������ļ�·��  
#define BELL_SOUND L".\\Love-as-you-please.wav"  
#define DOGBARK_SOUND L".\\dog.wav"  

int MyClock::run(bool aIsPlayDogBark)
{
#ifdef  OS_WINDOWS    
    while (true) {
        SYSTEMTIME st;
        GetLocalTime(&st); // ��ȡ����ʱ��  

        // ����Ƿ񵽴�ÿСʱ�ĵ�45����
        int interval = 40;
        int elapseTime = st.wMinute % interval;
        if (elapseTime == 0) {
            system("cls"); // ����  
            std::cout << "��Ϣʱ�䵽�ˣ���������..." << std::endl;
            // ��������  
            int retPlaySound = 0;
            if (aIsPlayDogBark)
            {
                retPlaySound = sndPlaySound(DOGBARK_SOUND, SND_FILENAME | SND_ASYNC);
            }
            else {
                retPlaySound = sndPlaySound(BELL_SOUND, SND_FILENAME | SND_ASYNC);
            }
            
            if (retPlaySound == 0) {
                std::cerr << "�޷����������ļ���" << std::endl;
            }
            // Ϊ�˱�����45��0�뵽45��59��֮�䷴�����ţ���������һ�����ݵ���ʱ  
            // ����������ʹ�õ���ѭ����Sleep�ķ�ʽ�������������ʱ������Խϳ�  
            // ����ȴ�����һ��Сʱ�Ŀ�ʼ�ټ�飨��ȥ�Ѿ���ȥ��������  
            // ��Ϊ�˼��������������ֱ�ӵȴ�һ�����ټ�飨���������ظ�������  
            Sleep(60000); // �ȴ�һ���ӣ�60�� * 1000���룩  
            // ע�⣺�����Sleep(60000)�ᵼ����45��01�뵽45��59��֮�䲻����ʱ��  
            // ����һ���򵥵Ĵ�����ʽ�������Ҫ����ȷ�Ŀ��ƣ�����ʹ�ø����ӵ��߼�  
            // �����¼��һ�β��ŵ�ʱ�䣬Ȼ����㵽��һ��Ӧ�ò��ŵ�ʱ����  
        }
        else {
            // �������45���ӣ���ȴ�һ��ʱ���ټ��  
            // ������Ը�����Ҫ�����ȴ�ʱ�䣬����ÿ���Ӽ��һ��  
            Sleep(1000); // �ȴ�1���� 

            system("cls"); // ����  
            int waitTime = interval - elapseTime;
            printf("���� %d ����\r", waitTime);
            //std::cout << "����" << waitTime << "����..." << std::endl;
        }
    }

    // ע�⣺���ʾ��������һ������ѭ������Ҫ�ֶ�ֹͣ����رտ���̨���ڣ�  
    // ��ʵ��Ӧ���У��������Ҫʵ��һ�������ŵ��˳�����  
#endif // #ifdef  OS_WINDOWS
    return 0;
}
