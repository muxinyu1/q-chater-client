#include "variable.h"

Variable::Variable()
{

}

QString r1="ff",g1="99",b1="00",r2="00",g2="00",b2="00";
QString file="1";

QString _r1="ff",_g1="99",_b1="00",_r2="00",_g2="00",_b2="00";
QString _file="1";

const QString styleStr="QLabel#label{background-image:url(:/new/patterns/patterns/%1.png);"
                       "background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #%2,stop:1 #%3);"
                       "background-position:center;%4}";
