#ifndef PCLVIEWER_H
#define PCLVIEWER_H

#include <iostream>
#include <sstream>

// Qt
#include <QMainWindow>

#include <qgraphicsscene.h>
#include <QtGui/QPixmap>
#include <QtCore/QProcess>

// Point Cloud Library
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/io/pcd_io.h>
#include <pcl/io/png_io.h>

// Visualization Toolkit (VTK)
#include <vtkRenderWindow.h>

typedef pcl::PointXYZRGBA PointT;
typedef pcl::PointCloud<PointT> PointCloudT;

namespace Ui
{
  class PCLViewer;
}

class PCLViewer : public QMainWindow
{
  Q_OBJECT

public:
  explicit PCLViewer (QWidget *parent = 0);
  ~PCLViewer ();


protected:
  boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer;
  PointCloudT::Ptr cloud;

private slots:
  void on_pushButton_clicked();

  void on_pushButton_2_clicked();

  void on_pushButton_3_clicked();

private:
  Ui::PCLViewer *ui;
  int frame;
  int frame_max;

  QGraphicsScene *scene;
  QPixmap image;

};

#endif // PCLVIEWER_H
