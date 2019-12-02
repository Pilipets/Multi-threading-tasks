package scheduling_simulator.utils.process;

public class sProcess extends Process implements Comparable {
  private static int counter = 0;
  public int id;
  public int arrivalTime = 0;
  public float responseRatio = 0;
  public float wt,tt,ntt;

  public sProcess (int cputime, int ioblocking, int cpudone, int ionext, int numblocked) {
    super(cputime, ioblocking, cpudone, ionext, numblocked);
    this.id = counter++;
  }
  public sProcess (int cputime, int ioblocking, int arrivalTime) {
    super(cputime, ioblocking, 0,0,0);
    this.arrivalTime = arrivalTime;
    this.id = counter++;
  }

  public sProcess() {
    super();
  }

  public void updateResponseRatio(int numThreads, int compTime){
    int waitingTime = compTime - arrivalTime;
    if(waitingTime < 0 || cpudone == cputime)
      responseRatio = Integer.MAX_VALUE;
    else if(waitingTime == 0){
      responseRatio = 0;
    }
    else{
      responseRatio = cpudone*numThreads/(float)waitingTime;
    }
  }
  @Override
  public int compareTo(Object o) {
    sProcess other = (sProcess)o;
    return Float.compare(this.responseRatio, other.responseRatio);
  }
}
