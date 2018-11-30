# comp220-worksheetA

Currently for my prototype I've done ligthing, which still could be further improved. 
For this I could get some help from [here](https://learnopengl.com/index.php?p=Advanced-Lighting/Advanced-Lighting).
In my current version, I have implemented Blinn-Phong lighting, which includes ambient, diffuse and specular ones.
But having better one would benefit my planned prototype.

In the document file called COMP220-Debugging I've shown the procces of me struggling with showing a loaded mesh. 
Thanks to Louis and his greatest skills of helping others, I managed to fix that and it's now showing the mesh. 
It has minimalistic explanation of why this was happening with screenshots of the window and values, that were 
being given.

## Next iteration
For the next iteration I would like to implement sky. For this skyboxes would fit very well. 
Implmeneting skybox [this tutorial](https://learnopengl.com/index.php?p=Advanced-OpenGL/Cubemaps) would help a lot.
In that tutorial, there are also downloadable [skyboxes](http://www.custommapmakers.org/skyboxes.php), which might be very useful. 

Also, trying to render at least one tree would be very beneficial for my prototype, as the game itself is located in a forest. 
This will be challenging, as rendering trees is pretty hard in terms of optimization. 
But there are some papers that explain and show how this works as well as website called [Speed Tree](https://store.speedtree.com). 

In addition to that, implementing water would be an interesting idea. This would fit the environenment that I'm trying 
to make for my prototype. Simulating water is not a simple task, but nonetheless it's possible. This can be done by 
some calculations in .GLSL file and is shown [here](http://jayconrod.com/posts/34/water-simulation-in-glsl).