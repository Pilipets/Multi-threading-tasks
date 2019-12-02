package scheduling_simulator;

public class sProcess {
  public int cputime;
  public int ioblocking;
  public int cpudone;
  public int ionext;
  public int numblocked;
  public int completed;
  public int arrivalTime;
  public int blocked;
  public sProcess(){

  }
  public sProcess (int cputime, int ioblocking, int cpudone, int ionext, int numblocked) {
    this.cputime = cputime;
    this.ioblocking = ioblocking;
    this.cpudone = cpudone;
    this.ionext = ionext;
    this.numblocked = numblocked;
    this.completed = 0;
    this.arrivalTime = 0;
  }
  public sProcess (int cputime, int ioblocking, int cpudone, int ionext,
                   int numblocked, int arrivalTime) {
    this(cputime, ioblocking, cpudone, ionext, numblocked);
    this.arrivalTime = arrivalTime;
  }
}
