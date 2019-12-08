package scheduling_simulator.algo;

import scheduling_simulator.utils.sProcess;

import java.lang.reflect.Array;
import java.util.*;

public class HRRNScheduler {
    private List<sProcess> pVec;
    private int numTasks;
    private int completedTasks = 0;
    private sProcess curProcess = null;

    public HRRNScheduler(Vector<sProcess> processVector){
        this.pVec = new LinkedList<>(processVector);
        this.numTasks = processVector.size();
        init();
    }
    private void init(){
        Collections.sort(pVec, new Comparator<sProcess>() {
            @Override
            public int compare(sProcess p1, sProcess p2) {
                return Integer.compare(p1.arrivalTime, p2.arrivalTime);
            }
        }
        );
    }
    public void markCompletedOne(sProcess p){
        completedTasks += 1;
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
    public sProcess getNextProcess(int compTime){
        float hrr = Integer.MIN_VALUE;
        for(sProcess p: pVec){
            if(p.arrivalTime <= compTime && p != curProcess && p.cpudone != p.cputime){
                float temp = (p.cputime + compTime - p.arrivalTime)/(float)p.cputime;
                p.responseRatio = temp;
                if(hrr < temp){
                    hrr = temp;
                    curProcess = p;
                }
            }
        }
        return curProcess;
    }
}
