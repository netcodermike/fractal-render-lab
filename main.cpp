#include <QtWidgets>
#include <QTemporaryDir>
#include <cmath>
#include <complex>
#include <vector>
#include <algorithm>
#include <stdexcept>

int escape(double x,double y,int limit){double a=0,b=0;int n=0;while(a*a+b*b<=4&&n<limit){double next=a*a-b*b+x;b=2*a*b+y;a=next;n++;}return n;}
QImage make(const QString&setting){auto parts=(setting.isEmpty()?QString("-0.5,0,1"):setting).split(',');if(parts.size()!=3)throw std::runtime_error("Enter centerX,centerY,zoom");bool a,b,c;double cx=parts[0].toDouble(&a),cy=parts[1].toDouble(&b),zoom=parts[2].toDouble(&c);if(!a||!b||!c||!std::isfinite(cx)||!std::isfinite(cy)||!std::isfinite(zoom)||zoom<1||zoom>100000||std::abs(cx)>4||std::abs(cy)>4)throw std::runtime_error("Invalid center or zoom");QImage image(800,500,QImage::Format_RGB32);for(int y=0;y<500;y++)for(int x=0;x<800;x++){int n=escape(cx+(x-400)*3.2/800/zoom,cy+(y-250)*3.2/800/zoom,300);image.setPixelColor(x,y,n==300?QColor("#0e1725"):QColor::fromHsv((n*7)%360,190,245));}return image;}
bool test(){if(escape(0,0,300)!=300||escape(2,2,300)>=5)return false;auto image=make("-0.5,0,1");return image.width()==800&&image.pixel(400,250)!=image.pixel(0,0);}

int main(int argc,char**argv){if(argc==2&&QString(argv[1])=="--self-test"){QCoreApplication a(argc,argv);return test()?0:1;}QApplication a(argc,argv);QWidget w;w.setWindowTitle("Fractal Render Lab");w.resize(1000,750);auto layout=new QVBoxLayout(&w);layout->addWidget(new QLabel("Mandelbrot renderer. Enter centerX,centerY,zoom (zoom 1–100000)."));auto controls=new QHBoxLayout;auto input=new QLineEdit;input->setPlaceholderText("-0.5,0,1");controls->addWidget(input);auto render=new QPushButton("Render / analyze");controls->addWidget(render);auto save=new QPushButton("Export PNG");controls->addWidget(save);layout->addLayout(controls);auto view=new QLabel;view->setAlignment(Qt::AlignCenter);layout->addWidget(view,1);QImage image;QObject::connect(render,&QPushButton::clicked,[&](){try{image=make(input->text());view->setPixmap(QPixmap::fromImage(image).scaled(920,600,Qt::KeepAspectRatio));}catch(const std::exception&e){QMessageBox::warning(&w,"Input",e.what());}});QObject::connect(save,&QPushButton::clicked,[&](){if(image.isNull())return;auto p=QFileDialog::getSaveFileName(&w,"Export image",{},"PNG (*.png)");if(!p.isEmpty()&&!image.save(p,"PNG"))QMessageBox::warning(&w,"Export","Write failed");});w.show();return a.exec();}
