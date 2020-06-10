
#include <iostream>

template<typename TFilter>
ITKComputationThread<TFilter>::ITKComputationThread()
{
  this->Filter = NULL;
}

template<typename TFilter>
void ITKComputationThread<TFilter>::run()
{
  std::cout << "ProgressThread::run()" << std::endl;
  // When the thread is started, emit the signal to start the marquee progress bar
  emit StartProgressBarSignal();

  this->Filter->Update();

  // When the function is finished, end the thread
  exit();
}
