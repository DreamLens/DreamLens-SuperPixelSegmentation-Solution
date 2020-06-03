#ifndef ITKComputationThread_H
#define ITKComputationThread_H

#include <QThread>

class FilterComputationThreadNonTemplated : public QThread
{
Q_OBJECT
signals:
  // This signal is emitted to start the progress b