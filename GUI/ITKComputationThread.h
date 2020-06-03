#ifndef ITKComputationThread_H
#define ITKComputationThread_H

#include <QThread>

class FilterComputationThreadNonTemplated : public QThread
{
Q_OBJECT
signals:
  // This signal is emitted to start the progress bar
  void StartProgressBarSignal();

  // This signal is emitted to stop the progress bar
  void StopProgressB