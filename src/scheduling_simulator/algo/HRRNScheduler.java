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
    private int compTime = 0;
    private sProcess curProcess = null, nextProcess = null;

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
                        return p1.compareTo(p2);
                    }
                }
        );
    }
    public void markCompletedOne(sProcess p){
        completedTasks += 1;
        pVec.remove(p);
        curProcess = null;
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
        compTime += 1;
    }
    public sProcess getNextProcess(){
        if(curProcess == null){
            curProcess = pVec.get(0);
            if(pVec.size() > 1)
                nextProcess = pVec.get(1);
        }
        else{
            curProcess.updateResponseRatio(numTasks, compTime);
            if(curProcess.compareTo(nextProcess) == 1){
                Collections.sort(pVec, new Comparator<sProcess>() {
                            @Override
                            public int compare(sProcess p1, sProcess p2) {
                                return p1.compareTo(p2);
                            }
                        }
                );
                curProcess = pVec.get(0);
                if(pVec.size() > 1)
                    nextProcess = pVec.get(1);
            }
        }
        return curProcess;
    }
}
