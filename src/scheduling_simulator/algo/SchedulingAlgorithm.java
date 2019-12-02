// Run() is called from Scheduling.main() and is where
// the scheduling algorithm written by the user resides.
// User modification should occur within the Run() function.

package scheduling_simulator.algo;

import scheduling_simulator.utils.ProcessInfoPrinter;
import scheduling_simulator.utils.Results;
import scheduling_simulator.utils.sProcess;

import java.util.Vector;
import java.io.*;

public class SchedulingAlgorithm {

  public static Results Run(int runTime, Vector processVector, Results result) {
    String resultsFile = "result_data/Summary-Processes";
    result.schedulingType = "Batch (Nonpreemptive)";
    result.schedulingName = "Guaranteed Scheduling";

    HRRNScheduler scheduler = new HRRNScheduler(processVector, runTime);
    int compTime = 0;
    boolean takeNewProcess = false;
    try {
      PrintStream out = new PrintStream(new FileOutputStream(resultsFile));
      while (compTime < runTime) {
        sProcess curProcess = scheduler.getNextProcess();
        if (curProcess.cpudone == curProcess.cputime) {
          scheduler.markCompletedOne(curProcess);
          ProcessInfoPrinter.print(out, curProcess, ProcessInfoPrinter.Status.Completed);
          takeNewProcess = true;
          if(scheduler.isEmpty()){
            result.compuTime = compTime;
            out.close();
            return result;
          }
        }      
        else if (curProcess.ioblocking == curProcess.ionext) {
          scheduler.markBlockedOne(curProcess);
          ProcessInfoPrinter.print(out, curProcess, ProcessInfoPrinter.Status.Blocked);
          takeNewProcess = true;
        }
        else{
          ProcessInfoPrinter.print(out, curProcess, ProcessInfoPrinter.Status.Registered);
          takeNewProcess = false;
        }

        if(!takeNewProcess){
          scheduler.updateRunning(curProcess);
          compTime++;
        }
      }
      out.close();
    } catch (IOException e) { /* Handle exceptions */ }
    result.compuTime = compTime;
    return result;
  }
}
