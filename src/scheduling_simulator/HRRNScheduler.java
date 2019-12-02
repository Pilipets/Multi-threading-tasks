package scheduling_simulator;

import java.util.Vector;

public class HRRNScheduler {
    private Vector<sProcess> pVec;
    private int size;
    private int runTime;
    private int compTime;
    private sProcess curProcess;
    public HRRNScheduler(Vector<sProcess> processVector, int runTime){
        this.pVec = processVector;
        this.size = processVector.size();
        this.runTime = runTime;
        this.compTime = 0;
    }
    public void markCompletedOne(int index){
        curProcess = pVec.elementAt(index);
        curProcess.completed = 1;
    }
    public void markBlockedOne(int index){
        curProcess = pVec.elementAt(index);
        curProcess.ionext = 0;
        curProcess.numblocked += 1;
    }
    public void updateRunning(int index){
        curProcess = pVec.elementAt(index);
        curProcess.cpudone += 1;
        if(curProcess.ioblocking > 0)
            curProcess.ionext += 1;
    }
    public int getNextProcessIndex(int previous){
        int nextIndex = 0;
        float hrr = Integer.MIN_VALUE;
        for (int i = 0; i < size; i++) {
            curProcess = pVec.elementAt(i);
            if (curProcess.arrivalTime <= this.runTime && curProcess.completed != 1 &&
                    curProcess.blocked != 1 && i != previous) {
                // Calculating Response Ratio
                float temp = (curProcess.cputime + (this.runTime - curProcess.arrivalTime)) / curProcess.cputime;
                if (hrr < temp) {
                    hrr = temp;
                    nextIndex = i;
                }
            }
        }
        return nextIndex;
    }

    public sProcess elementAt(int index) {
        return pVec.elementAt(index);
    }
}
