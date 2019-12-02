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
  public static int NextTimePoint(HRRNScheduler scheduler){
    Vector<sProcess> pVec = scheduler.getTasks();

    int min_time = Integer.MAX_VALUE;
    for(sProcess p: pVec){
      min_time = Math.min(p.cputime-p.cputime, min_time);
      min_time = Math.min(p.ioblocking-p.ionext, min_time);
    }
    return min_time;
  }
  public static int GetNextArrivalPoint(HRRNScheduler scheduler){
    Vector<sProcess> pVec = scheduler.getTasks();

    int min_at = Integer.MAX_VALUE;
    for(sProcess p: pVec){
      if(p.arrivalTime < min_at)
        min_at = p.arrivalTime;
    }
    return min_at;
  }
  public static Results Run(int runTime, Vector processVector, Results result) {
    String resultsFile = "result_data/Summary-Processes";
    result.schedulingType = "Batch (Nonpreemptive)";
    result.schedulingName = "Guaranteed Scheduling";

    HRRNScheduler scheduler = new HRRNScheduler(processVector, runTime);
    int compTime = 0;
    try {
      PrintStream out = new PrintStream(new FileOutputStream(resultsFile));
      sProcess curProcess = scheduler.getNextProcess(compTime);
      while (compTime < runTime) {
        while (compTime < runTime && curProcess == null) {
          compTime += 1;
          curProcess = scheduler.getNextProcess(compTime);
        }

        if(compTime != runTime)
          ProcessInfoPrinter.print(out, curProcess, ProcessInfoPrinter.Status.Registered);
        while (compTime < runTime) {
          boolean takeNewProcess = false;
          if (curProcess.cpudone == curProcess.cputime) {
            scheduler.markCompletedOne(curProcess);
            ProcessInfoPrinter.print(out, curProcess, ProcessInfoPrinter.Status.Completed);
            if (scheduler.isEmpty()) {
              result.compuTime = compTime;
              out.close();
              return result;
            }
            takeNewProcess = true;
          }
          if (curProcess.ioblocking == curProcess.ionext) {
            scheduler.markBlockedOne(curProcess);
            ProcessInfoPrinter.print(out, curProcess, ProcessInfoPrinter.Status.Blocked);
            takeNewProcess = true;
          }

          if(takeNewProcess){
            curProcess = scheduler.getNextProcess(compTime);
            if(curProcess == null)
              break;
            ProcessInfoPrinter.print(out, curProcess, ProcessInfoPrinter.Status.Registered);
          }
          scheduler.updateRunning(curProcess);
          compTime += 1;
        }
      }
      out.close();
    } catch (IOException e) { /* Handle exceptions */ }
    result.compuTime = compTime;
    return result;
  }
}
