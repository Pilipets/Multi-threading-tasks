package scheduling_simulator.utils;

public class sProcess implements Comparable{
  private static int counter = 0;
  public int cputime;
  public int ioblocking;
  public int cpudone = 0;
  public int ionext = 0;
  public int numblocked = 0;
  public int arrivalTime = 0;
  public float responseRatio = 0;
  public int id;
  public sProcess(){

  }
  public sProcess (int cputime, int ioblocking, int cpudone, int ionext, int numblocked) {
    this.cputime = cputime;
    this.ioblocking = ioblocking;
    this.cpudone = cpudone;
    this.ionext = ionext;
    this.numblocked = numblocked;
    this.id = counter++;
  }
  public sProcess (int cputime, int ioblocking, int arrivalTime) {
    this.cputime = cputime;
    this.ioblocking = ioblocking;
    this.arrivalTime = arrivalTime;
  }
  /*public void updateResponseRatio(int numTasks, int compTime){
    this.responseRatio = this.cpudone*(float)numTasks/(compTime-this.arrivalTime);
  }*/
  @Override
  public int compareTo(Object o) {
    sProcess other = (sProcess)o;
    return Float.compare(this.responseRatio, other.responseRatio);
  }
}
