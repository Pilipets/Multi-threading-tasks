package scheduling_simulator.utils;

public class sProcess implements Comparable{
  public int cputime;
  public int ioblocking;
  public int cpudone;
  public int ionext;
  public int numblocked;
  public int completed;
  public int arrivalTime;
  public int blocked;
  public int id;
  private float responseRatio;
  private static int counter = 0;
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
    this.id = counter++;
  }
  public sProcess (int cputime, int ioblocking, int cpudone, int ionext,
                   int numblocked, int arrivalTime) {
    this(cputime, ioblocking, cpudone, ionext, numblocked);
    this.arrivalTime = arrivalTime;
    this.responseRatio = 0;
  }
  public void updateResponseRatio(int numTasks, int compTime){
    this.responseRatio = this.cpudone*(float)numTasks/(compTime-this.arrivalTime);
  }
  @Override
  public int compareTo(Object o) {
    sProcess other = (sProcess)o;
    return Float.compare(this.responseRatio, other.responseRatio);
  }
}
