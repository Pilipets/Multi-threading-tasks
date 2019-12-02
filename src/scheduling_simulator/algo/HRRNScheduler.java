package scheduling_simulator.algo;

import scheduling_simulator.utils.sProcess;

import java.util.Collections;
import java.util.Comparator;
import java.util.Vector;

public class HRRNScheduler {
    private Vector<sProcess> pVec;
    private int numTasks;
    private int maxTime;
    private int completedTasks = 0;
    private sProcess curProcess = null;

    public HRRNScheduler(Vector<sProcess> processVector, int maxTime){
        this.pVec = processVector;
        this.numTasks = processVector.size();
        this.maxTime = maxTime;
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
