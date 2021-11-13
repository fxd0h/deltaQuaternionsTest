#include <stdio.h>
#include "cqrlib.h"

int main(){
    unsigned int counter=0;
    CQRQuaternionHandle  actualQ;
    CQRQuaternionHandle  startQ;
    CQRQuaternionHandle  offsetQ;
    CQRQuaternionHandle  resultQ;
    CQRQuaternionHandle deltaQ;
    CQRQuaternionHandle startRotationQ,endRotationQ,lastRotationQ,invQ;

    double Xoffset,Xresult,Xacc;
    double Yoffset,Yresult,Yacc;
    double Zoffset,Zresult,Zacc;    



    Xoffset = 1.0f /(180/M_PI);
    Yoffset = -10.0f /(180/M_PI);
    Zoffset = 32.3333f/(180/M_PI);
    Zacc=0;
    Yacc=0;
    Xacc=0;
    CQRCreateEmptyQuaternion(&startQ);
    CQRCreateEmptyQuaternion(&actualQ);
    CQRCreateEmptyQuaternion(&offsetQ);
    CQRCreateEmptyQuaternion(&resultQ);

    CQRCreateEmptyQuaternion(&lastRotationQ);
    
    CQRCreateEmptyQuaternion(&invQ);

    CQRCreateEmptyQuaternion(&startRotationQ);
    CQRCreateEmptyQuaternion(&endRotationQ);
    
    CQRCreateEmptyQuaternion(&deltaQ);
    CQRCreateEmptyQuaternion(&invQ);


    CQRSetQuaternion(startQ,1,0,0,0);
    CQRSetQuaternion(actualQ,1,0,0,0);
    CQRSetQuaternion(lastRotationQ,1,0,0,0);

    CQRAngles2Quaternion(offsetQ,Xoffset,Yoffset,Zoffset);

    for (counter=0;counter<700;counter++){

        // add offestQ to actualQ
        CQRMultiply(resultQ,actualQ,offsetQ);
        //set actualQ as the result of the multiplication
        CQRSetQuaternion(actualQ,resultQ->w,resultQ->x,resultQ->y,resultQ->z);
        
        // actualQ - lsatRotationQ
        //qDelta = qTo * qFrom.inverse()


        CQRInverse (invQ,lastRotationQ ) ;

        CQRMultiply(deltaQ,actualQ,invQ);


        CQRSetQuaternion(lastRotationQ,actualQ->w,actualQ->x,actualQ->y,actualQ->z);

        CQRQuaternion2Angles(&Xresult,&Yresult,&Zresult,deltaQ);
        Zacc += Zresult;
        Yacc += Yresult;
        Xacc += Xresult;
        printf("\nDelta X:%f Y:%f Z:%f\nAccumul  X:%f Y:%f Z:%f\n", Xresult*(180/M_PI),Yresult*(180/M_PI),Zresult*(180/M_PI),
                Xacc*(180/M_PI),Yacc*(180/M_PI),Zacc*(180/M_PI));

        CQRQuaternion2Angles(&Xresult,&Yresult,&Zresult,actualQ);
        printf("Rotation X:%f Y:%f Z:%f\n  Result X: %f Y: %f Z: %f  W: %f J: %f K: %f I: %f\n",
                Xoffset*(counter+1)*(180/M_PI),Yoffset*(counter+1)*(180/M_PI),Zoffset*(counter+1)*(180/M_PI),
                Xresult*(180/M_PI),Yresult*(180/M_PI),Zresult*(180/M_PI),actualQ->w,actualQ->x,actualQ->y,actualQ->z);           
    }

}

