#include "pclviewer.h"
#include "../build/ui_pclviewer.h"



PCLViewer::PCLViewer (QWidget *parent) :
  QMainWindow (parent),
  ui (new Ui::PCLViewer)
{
  ui->setupUi (this);
  this->setWindowTitle ("PCL viewer");

  //set frame to 1
  frame = 1;
  frame_max = 12;

  // Setup the cloud pointer
  cloud.reset (new PointCloudT);
  pcl::io::loadPCDFile("/home/shiv/Research/qt-pcl-example/pcd_files/pcd_1.pcd" , *cloud);

  //set image path
  QString path = QString::fromStdString("/home/shiv/Research/qt-pcl-example/images/image_1.png");

  //save image from cloud as png file
  pcl::io::savePNGFile(path.toStdString(), *cloud, "rgb");

  //load image
  image.load(path);
  scene = new QGraphicsScene(this);
  scene->addPixmap(image);
  scene->setSceneRect(image.rect());

  ui->mainImage->setScene(scene);

  // Set up the QVTK window to display point cloud
  viewer.reset (new pcl::visualization::PCLVisualizer ("viewer", false));
  ui->qvtkWidget->SetRenderWindow (viewer->getRenderWindow ());
  viewer->setupInteractor (ui->qvtkWidget->GetInteractor (), ui->qvtkWidget->GetRenderWindow ());
  ui->qvtkWidget->update ();

  viewer->addPointCloud (cloud, "cloud");

  viewer->resetCamera ();
  ui->qvtkWidget->update ();
}

//move frame forward
void PCLViewer::on_pushButton_clicked()
{
    if(++frame > frame_max)
        frame = frame_max;

    //update point cloud
    QString pcd_path;
    pcd_path = "/home/shiv/Research/qt-pcl-example/pcd_files/pcd_" + QString::number(frame) + ".pcd";

    pcl::io::loadPCDFile(pcd_path.toStdString() , *cloud);

    viewer->updatePointCloud (cloud, "cloud");
    ui->qvtkWidget->update ();

    //update image
    QString img_path;
    img_path = "/home/shiv/Research/qt-pcl-example/images/image_" + QString::number(frame) + ".png";

    //save image from cloud as png file
    pcl::io::savePNGFile(img_path.toStdString(), *cloud, "rgb");

    image.load(img_path);
    scene = new QGraphicsScene(this);
    scene->addPixmap(image);
    scene->setSceneRect(image.rect());

    ui->mainImage->setScene(scene);


}

//move frame backward
void PCLViewer::on_pushButton_2_clicked()
{
    if(--frame < 1)
        frame = 1;

    //update point cloud
    QString pcd_path;
    pcd_path = "/home/shiv/Research/qt-pcl-example/pcd_files/pcd_" + QString::number(frame) + ".pcd";

    pcl::io::loadPCDFile(pcd_path.toStdString() , *cloud);

    viewer->updatePointCloud (cloud, "cloud");
    ui->qvtkWidget->update ();

    //update image
    QString img_path;
    img_path = "/home/shiv/Research/qt-pcl-example/images/image_" + QString::number(frame) + ".png";

    image.load(img_path);
    scene = new QGraphicsScene(this);
    scene->addPixmap(image);
    scene->setSceneRect(image.rect());

    ui->mainImage->setScene(scene);


}

PCLViewer::~PCLViewer ()
{
  delete ui;
}

void PCLViewer::on_pushButton_3_clicked()
{

    for(int c = 0; c < frame_max; c++)
    {
        //update point cloud
        QString pcd_path;
        pcd_path = "/home/shiv/Research/qt-pcl-example/pcd_files/pcd_" + QString::number(c) + ".pcd";

        pcl::io::loadPCDFile(pcd_path.toStdString() , *cloud);

        //create image
        QString img_path;
        img_path = "/home/shiv/Research/qt-pcl-example/images/image_" + QString::number(c) + ".png";

        //save image from cloud as png file
        pcl::io::savePNGFile(img_path.toStdString(), *cloud, "rgb");
    }

    QProcess::execute(QString("python generate-video.py"));
}
