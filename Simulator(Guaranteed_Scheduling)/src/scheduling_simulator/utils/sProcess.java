package scheduling_simulator.utils;

public class sProcess{
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
    this.id = counter++;
  }
}
