package scheduling_simulator.algo;

import scheduling_simulator.utils.sProcess;

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
        init(processVector);
    }
    private void init(Vector<sProcess> processVector){
        //construct heap from Processes
    }
    public void markCompletedOne(sProcess p){
        completedTasks += 1;
        // deleteNode(p)
    }
    public boolean isEmpty(){
        return completedTasks == numTasks;
    }
    public void markBlockedOne(sProcess p){
        p.ionext = 0;
        p.numblocked += 1;
        p.updateResponseRatio(numTasks,compTime);
        // updateNode(p)
    }
    public void updateRunning(sProcess p){
        p.cpudone += 1;
        if(p.ioblocking > 0)
            p.ionext += 1;
        compTime += 1;
    }
    public sProcess getNextProcess(){
        if(curProcess == null){
            //Find curProcess, nextProcess
        }
        else{
            curProcess.updateResponseRatio(numTasks, compTime);
            if(curProcess.compareTo(nextProcess) == 1){
                // UpdateHeap(curProcess)
                // curProcess = nextProcess
                // Find nextProcess
            }
        }
        return curProcess;
    }
}
