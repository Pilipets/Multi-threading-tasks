package scheduling_simulator.algo;

import scheduling_simulator.utils.ProcessInfoPrinter;
import scheduling_simulator.utils.process.sProcess;

import java.security.KeyPair;
import java.util.Collections;
import java.util.Comparator;
import java.util.Vector;

public class GuaranteedScheduler {
    private Vector<sProcess> pVec;
    private int numTasks;
    private int completedTasks = 0;
    private sProcess curProcess = null, nextProcess = null;

    private void updateProcessesOrder(int compTime){
        for(sProcess p: pVec){
            p.updateResponseRatio(numTasks, compTime);
        }
        Collections.sort(pVec, (p1, p2) -> p1.compareTo(p2));
        curProcess = pVec.size() > 0 && pVec.get(0).responseRatio < Integer.MAX_VALUE ? pVec.get(0) : null;
        nextProcess = pVec.size() > 1 && pVec.get(1).responseRatio < Integer.MAX_VALUE? pVec.get(1) : null;
    }
    public GuaranteedScheduler(Vector<sProcess> processVector){
        this.pVec = new Vector<>(processVector);
        this.numTasks = processVector.size();
        init();
    }
    private void init(){
        updateProcessesOrder(0);
        curProcess.responseRatio = 0;
    }
    public void markCompletedOne(sProcess p, int compTime){
        completedTasks += 1;

        // Calculation of waiting time
        p.wt = compTime - p.arrivalTime - p.cputime;
        // Calculation of Turn Around Time
        p.tt = compTime - p.arrivalTime;
        // Calculation of Normalized Turn Around Time
        p.ntt = ((float)p.tt / p.cputime);

        pVec.remove(p);
    }
    public boolean isEmpty(){
        return completedTasks == numTasks;
    }
    public void markBlockedOne(sProcess p){
        p.ionext = 0;
        p.numblocked += 1;
    }
    public void updateRunning(sProcess p){
        p.cpudone += 1;
        if(p.ioblocking > 0)
            p.ionext += 1;
    }
    public Vector<sProcess> getTasks(){
        return pVec;
    }
    public boolean takeNewProcess(int compTime){
        if(curProcess == null || nextProcess == null)
            return true;
        nextProcess.updateResponseRatio(numTasks, compTime);
        curProcess.updateResponseRatio(numTasks, compTime);
        return curProcess.responseRatio > nextProcess.responseRatio;
    }
    public sProcess getNextProcess(int compTime){
        if(curProcess == null || nextProcess == null)
            return curProcess;

        updateProcessesOrder(compTime);
        return curProcess;
    }
}
