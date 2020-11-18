# Minimum Enclosing Circle Algorithms And B-spline Curves
 
- I'm gonna explain to you what is that Minimum Enclosing Circle and B-splines curves

## MEC definiton

Assume that you have several points that has X and Y coordinates such as (4,5) e.g.And you are going to create a circle with these points.If you create or draw this circle ,
you have to supply to enclosing whole numbers inside of circle.But that's the point that you have to draw a circle that minimum enclosing circle.In other words , you have to draw a circle that is smallest enclosing whole given points inside of itself. Indeed , the basic idea of MEC is simple , it depends several mathematical equations and given data points(N).If given two numbers , process will be very easy.You should implement <b>pisagor therom</b> to two points and you will find radius and center coordinates belong to radius. If number of given points bigger than 2 then you should not implement <b>pisagor therom</b> , you should implement equation that contain 2 steps process about circle equation.

-	  `x² + y² + 2GX + 2fy + C = 0  (geenral circle equation)`
-  	`(x - h) ² + (y -k) ² = r²  (h is central of circle and r is radius)`

We will make process with depend these equation in code section when given number of points bigger than 2

#### `As you see , circles have enclosed whole given points.`

|<img src="/images/mec.png" height = "450" width = "450">|<img src="/images/mec2.png" height = "450" width = "450">|
|--------------------------------------------------------|---------------------------------------------------------|


## B-spline curves definition
B-spline curves is a curve that usually used for Computer Assistance Design (CAD) applications , definite for one group data points , used for numbers derivate and integration.it usually appeares a cubic form. B-spline curves do not pass through data points so it looks like smallest square curves.Purpose is with the b-spline curves that drawing b-spline lines inside of circle and the line have to pass through the closest place from the points.

#### First image is general expression image belong to b-splines.You show that this line has several control points ,we can say that thanks to control points lines changes it's way .`Second image at the below is my MEC project's output `. There is a circle that enclosing whole given points we can say that there is a minimum enclosing circle also inside of the circle a line have drowen among whole points , and it passed through closest place from the points.

|<img src="/images/b_spline.png" width="450" height="450"> |<img src="/images/lab_1.png" width="450" height="450">|
|----------------------------------------------------------|------------------------------------------------------|



