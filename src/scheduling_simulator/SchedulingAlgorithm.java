// Run() is called from Scheduling.main() and is where
// the scheduling algorithm written by the user resides.
// User modification should occur within the Run() function.

package scheduling_simulator;

import java.util.Vector;
import java.io.*;

public class SchedulingAlgorithm {

  public static Results Run(int runtime, Vector processVector, Results result) {
    HRRNScheduler scheduler = new HRRNScheduler(processVector, runtime);
    int comptime = 0;
    int pIndex = 0;
    int size = processVector.size();
    int completed = 0;
    String resultsFile = "Summary-Processes";

    result.schedulingType = "Batch (Nonpreemptive)";
    result.schedulingName = "Guaranteed Scheduling";
    try {
      //BufferedWriter out = new BufferedWriter(new FileWriter(resultsFile));
      //OutputStream out = new FileOutputStream(resultsFile);
      PrintStream out = new PrintStream(new FileOutputStream(resultsFile));
      sProcess curProcess = scheduler.elementAt(pIndex);
      out.println("Process: " + pIndex + " registered... (" + curProcess.cputime + " " +
              curProcess.ioblocking + " " + curProcess.cpudone + " " + curProcess.cpudone + ")");
      while (comptime < runtime) {

        if (curProcess.cpudone == curProcess.cputime) {
          scheduler.markCompletedOne(pIndex);
          completed++;
          out.println("Process: " + pIndex + " completed... (" + curProcess.cputime + " " +
                  curProcess.ioblocking + " " + curProcess.cpudone + " " + curProcess.cpudone + ")");
          if (completed == size) {
            result.compuTime = comptime;
            out.close();
            return result;
          }
          pIndex = scheduler.getNextProcessIndex(-1);
          curProcess = scheduler.elementAt(pIndex);
          out.println("Process: " + pIndex + " registered... (" + curProcess.cputime + " " +
                  curProcess.ioblocking + " " + curProcess.cpudone + " " + curProcess.cpudone + ")");
        }      
        if (curProcess.ioblocking == curProcess.ionext) {
          scheduler.markBlockedOne(pIndex);
          out.println("Process: " + pIndex + " I/O blocked... (" + curProcess.cputime + " " +
                  curProcess.ioblocking + " " + curProcess.cpudone + " " + curProcess.cpudone + ")");
          pIndex = scheduler.getNextProcessIndex(pIndex);
          curProcess = scheduler.elementAt(pIndex);
          out.println("Process: " + pIndex + " registered... (" + curProcess.cputime + " " +
                  curProcess.ioblocking + " " + curProcess.cpudone + " " + curProcess.cpudone + ")");
        }
        scheduler.updateRunning(pIndex);
        comptime++;
      }
      out.close();
    } catch (IOException e) { /* Handle exceptions */ }
    result.compuTime = comptime;
    return result;
  }
}
