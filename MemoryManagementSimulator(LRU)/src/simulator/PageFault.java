/* It is in this file, specifically the replacePage function that will
   be called by MemoryManagement when there is a page fault.  The
   users of this program should rewrite PageFault to implement the
   page replacement algorithm.
*/

// This PageFault file is an example of the FIFO simulator.Page Replacement
// Algorithm as described in the Memory Management section.

package simulator;
import my_implementation.LRUCache;

import java.util.*;

public class PageFault {

    /**
     * The page replacement algorithm for the memory management sumulator.
     * This method gets called whenever a page needs to be replaced.
     * <p>
     * The page replacement algorithm included with the simulator is
     * FIFO (first-in first-out).  A while or for loop should be used
     * to search through the current memory contents for a canidate
     * replacement page.  In the case of FIFO the while loop is used
     * to find the proper page while making sure that virtPageNum is
     * not exceeded.
     * <pre>
     *   simulator.Page page = ( simulator.Page ) mem.elementAt( oldestPage )
     * </pre>
     * This line brings the contents of the simulator.Page at oldestPage (a
     * specified integer) from the mem vector into the page object.
     * Next recall the contents of the target page, replacePageNum.
     * Set the physical memory address of the page to be added equal
     * to the page to be removed.
     * <pre>
     *   controlPanel.removePhysicalPage( oldestPage )
     * </pre>
     * Once a page is removed from memory it must also be reflected
     * graphically.  This line does so by removing the physical page
     * at the oldestPage value.  The page which will be added into
     * memory must also be displayed through the addPhysicalPage
     * function call.  One must also remember to reset the values of
     * the page which has just been removed from memory.
     *
     * @param mem is the vector which contains the contents of the pages
     *   in memory being simulated.  mem should be searched to find the
     *   proper page to remove, and modified to reflect any changes.
     * @param virtPageNum is the number of virtual pages in the
     *   simulator (set in Kernel.java).
     * @param replacePageNum is the requested page which caused the
     *   page fault.
     * @param controlPanel represents the graphical element of the
     *   simulator, and allows one to modify the current display.
     */
    public static void replacePage ( Vector mem , int virtPageNum , int replacePageNum , ControlPanel controlPanel )
    {
        int lruPage = -1;
        int lruTime = Integer.MIN_VALUE;

        for(int i = 0; i < virtPageNum; ++i){
            Page page = ( Page ) mem.elementAt( i );
            if ( page.physical != -1 ) {
                if (page.lastTouchTime > lruTime) {
                    lruTime = page.lastTouchTime;
                    lruPage = i;
                }
            }
        }
        Page page = ( Page ) mem.elementAt( lruPage );
        Page nextpage = ( Page ) mem.elementAt( replacePageNum );
        controlPanel.removePhysicalPage( lruPage );
        nextpage.physical = page.physical;
        controlPanel.addPhysicalPage( nextpage.physical , replacePageNum );
        page.inMemTime = 0;
        page.lastTouchTime = 0;
        page.R = 0;
        page.M = 0;
        page.physical = -1;
    }

    public static void replacePage (Vector mem , LRUCache cache, int virtPageNum , int replacePageNum , ControlPanel controlPanel )
    {
        int lruPage = cache.getFirstEntry();
        Page page = ( Page ) mem.elementAt( lruPage );
        Page nextpage = ( Page ) mem.elementAt( replacePageNum );
        controlPanel.removePhysicalPage( lruPage );
        nextpage.physical = page.physical;
        controlPanel.addPhysicalPage( nextpage.physical , replacePageNum );
        cache.put(replacePageNum, replacePageNum);
        page.inMemTime = 0;
        page.lastTouchTime = 0;
        page.R = 0;
        page.M = 0;
        page.physical = -1;
    }
}
