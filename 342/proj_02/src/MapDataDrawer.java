import java.util.*;
import java.io.*;
import java.awt.*;
import java.util.List;

public class MapDataDrawer {

    private int[][] grid;
    private int rows;
    private int cols;

    public int cols(){
        return this.cols;
    }

    public MapDataDrawer(String filename, int rows, int cols) {

        // initialize grid
        //read the data from the file into the grid
        try {
            Scanner sc = new Scanner(System.in);
            File file = new File(filename);
            sc = new Scanner(file);

            int i = 0, j = 0;
            this.rows = sc.nextInt(); //num rows
            this.cols = sc.nextInt(); //num columns
            this.rows = rows;
            this.cols = cols;

            grid = new int[rows][cols]; //init grid

            while (sc.hasNextInt()) {
                if (i < rows) {
                    grid[i][j] = sc.nextInt();
                    j++;
                    if (j == cols) {
                        j = 0;
                        i++;
                    }
                }
            }

            sc.close();
        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }

    /**
     * @return the min value in the entire grid
     */
    public int findMinValue() {
        int min;

        min = grid[0][0];
        for (int i = 0; i < this.rows; i++)
            for (int j = 0; j < this.cols; j++)
                if (grid[i][j] < min) min = grid[i][j];

        return min;
    }

    /**
     * @return the max value in the entire grid
     */
    public int findMaxValue() {
        int max;

        max = grid[0][0];
        for (int i = 0; i < this.rows; i++)
            for (int j = 0; j < this.cols; j++)
                if (grid[i][j] > max) max = grid[i][j];

        return max;
    }

    /**
     * @param col the column of the grid to check
     * @return the index of the row with the lowest value in the given col for the grid
     */
    public int indexOfMinInCol(int col) {
        int min, minRow = 0;

        min = grid[0][col];
        for (int i = 0; i < this.rows; i++)
            if (grid[i][col] < min) {
                min = grid[i][col];
                minRow = i;
            }
        return minRow;
    }

    /**
     * Draws the grid using the given Graphics object.
     * Colors should be grayscale values 0-255, scaled based on min/max values in grid
     */
    public void drawMap(Graphics g) {
        int c;  //calculated grayscale value
        int min = findMinValue();
        int max = findMaxValue();
        int delta = max - min;
        for(int j = 0; j < this.cols; j++){
            for(int i = 0; i < this.rows; i++){
                c = ((grid[i][j]-min)*255)/delta;
                g.setColor(new Color(c, c, c));
                g.fillRect(j,i,1,1);
            }
        }
    }



    /**
     * Find a path from West-to-East starting at given row.
     * Choose a foward step out of 3 possible forward locations, using greedy method described in assignment.
     *
     * @return the total change in elevation traveled from West-to-East
     */

    public int drawLowestElevPath(Graphics g, int row) {

        int curr, right, up, down;           // possible next steps elevations
        int deltaRight, deltaUp, deltaDown;  // change from previous step
        int currRowIndex = row;              // index of currentRow
        int totalElevationChange = 0;        // incremented elevation change every step

        //fill start coordinates
        g.fillRect(0,row,1,1);

        for(int i = 1; i < this.cols; i++){

            // find elev of all possible next steps if not
            // out of bounds
            curr = grid[currRowIndex][i-1];
            right = grid[currRowIndex][i];
            up   = (currRowIndex - 1 > 0)         ? grid[currRowIndex-1][i] : -1;
            down = (currRowIndex + 1 < this.rows) ? grid[currRowIndex+1][i] : -1;

            // find deltas
            deltaRight = Math.abs(curr - right);
            deltaUp = Math.abs(curr - up);
            deltaDown =  Math.abs(curr - down);

            // increment currRowIndex up or down if a better path is found
            if(down != -1 && up == -1){
                if(deltaDown < deltaRight)
                    currRowIndex += 1;
                else if(deltaDown == deltaRight)
                    currRowIndex += (Math.random() < 0.5) ? 1 : 0;
            }else if(down == -1 && up != -1){
                if(deltaUp < deltaRight)
                    currRowIndex -= 1;
                else if(deltaUp == deltaRight)
                    currRowIndex -= (Math.random() < 0.5) ? 1 : 0;
            }else if(down != -1 && up != -1){
                if(deltaUp < deltaDown){
                    if(deltaUp < deltaRight)
                        currRowIndex -= 1;
                    else if(deltaUp == deltaRight)
                        currRowIndex -= (Math.random() < 0.5) ? 1 : 0;
                }else{
                    if(deltaDown < deltaRight)
                        currRowIndex += 1;
                    else if(deltaDown == deltaRight)
                        currRowIndex += (Math.random() < 0.5) ? 1 : 0;
                }
            }

            // increment elev change
            totalElevationChange += Math.abs(curr - grid[currRowIndex][i]);
            // fill grid with coordinate
            g.fillRect(i, currRowIndex, 1,1);
        }

        return totalElevationChange;
    }


    /**
     * @return the index of the starting row for the lowest-elevation-change path in the entire grid.
     */
    public int indexOfLowestElevPath(Graphics g) {
        int min = drawLowestElevPath(g, 0);
        int minRow = 0;
        int delta;
        for(int i = 1; i < this.rows; i++){
            delta = drawLowestElevPath(g, i);
            if(delta < min) {
                minRow = i;
                min = delta;
            }
        }
        return minRow;
    }

    /**
     * Find a path from West-to-East starting at given row.
     * Choose a foward step out of 3 possible forward locations, using greedy method described in assignment.
     *
     * @return the total change in elevation traveled from East-to-West
     */

    public int drawLowestElevPathFromRight(Graphics g, int row) {

        int curr, left, up, down;           // possible next steps elevations
        int deltaLeft, deltaUp, deltaDown;  // change from previous step
        int currRowIndex = row;              // index of currentRow
        int totalElevationChange = 0;        // incremented elevation change every step

        //fill start coordinates
        g.fillRect(this.cols-1,row,1,1);

        for(int i = this.cols-2; i >= 0; i--){

            // find elev of all possible next steps if not
            // out of bounds
            curr = grid[currRowIndex][i+1];
            left = grid[currRowIndex][i];
            up   = (currRowIndex - 1 > 0)         ? grid[currRowIndex-1][i] : -1;
            down = (currRowIndex + 1 < this.rows) ? grid[currRowIndex+1][i] : -1;

            // find deltas
            deltaLeft = Math.abs(curr - left);
            deltaUp   = Math.abs(curr - up);
            deltaDown = Math.abs(curr - down);

            // increment currRowIndex up or down if a better path is found
            if(down != -1 && up == -1){
                if(deltaDown < deltaLeft)
                    currRowIndex += 1;
                else if(deltaDown == deltaLeft)
                    currRowIndex += (Math.random() < 0.5) ? 1 : 0;
            }else if(down == -1 && up != -1){
                if(deltaUp < deltaLeft)
                    currRowIndex -= 1;
                else if(deltaUp == deltaLeft)
                    currRowIndex -= (Math.random() < 0.5) ? 1 : 0;
            }else if(down != -1 && up != -1){
                if(deltaUp < deltaDown){
                    if(deltaUp < deltaLeft)
                        currRowIndex -= 1;
                    else if(deltaUp == deltaLeft)
                        currRowIndex -= (Math.random() < 0.5) ? 1 : 0;
                }else{
                    if(deltaDown < deltaLeft)
                        currRowIndex += 1;
                    else if(deltaDown == deltaLeft)
                        currRowIndex += (Math.random() < 0.5) ? 1 : 0;
                }
            }

            // increment elev change
            totalElevationChange += Math.abs(curr - grid[currRowIndex][i]);
            // fill grid with coordinate
            g.fillRect(i, currRowIndex, 1,1);
        }

        return totalElevationChange;
    }

    /**
     * @return the index of the starting row for the lowest-elevation-change path in the entire grid.
     */
    public int indexOfLowestElevPathFromRight(Graphics g) {
        int min = drawLowestElevPathFromRight(g, 0);
        int minRow = 0;
        int delta;
        for(int i = 1; i < this.rows; i++){
            delta = drawLowestElevPathFromRight(g, i);
            if(delta < min) {
                minRow = i;
                min = delta;
            }
        }
        return minRow;
    }
}