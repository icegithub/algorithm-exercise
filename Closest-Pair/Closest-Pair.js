function Point (x, y) {
    this.x = x;
    this.y = y;
}

Point.prototype.drawPoint = function(ctx) {
    if(this.x === undefined || this.x === null) 
        this.x = 100;

    if(this.y === undefined || this.y === null) 
        this.y = 100;
    
    var x = this.x;
    y = this.y;
    ctx.beginPath();
    ctx.fillStyle = "rgb(255, 0, 0)";
    //ctx.arc(x, y, r, start_angle, end_angle,...);
    ctx.arc(x, y, 5, 0, Math.PI*2, true);
    ctx.fill();
    // ctx.stroke();
    ctx.closePath();
}

function BruteForceClosestPoints(P, ctx) {
    var dmin = 10000;
    var index1, index2;
    var d;
    var i, j;
    for(i = 1; i < P.length - 1; i++) {
        for(j = i + 1; j < P.length; j++) {
            d = Math.pow(P[i].x - P[j].x, 2) + Math.pow(P[i].y - P[j].y, 2);
            if(d < dmin) {
                dmin = d;
                index1 = i;
                index2 = j;
            }
        }
    }

    // return index1, index2;
    console.log("index1: ", index1);
    console.log("index2: ", P[index2].x);
    ctx.beginPath();
    ctx.lineWidth = 4;
    ctx.strokeStyle = "#A300FF";
    ctx.moveTo(P[index1].x, P[index1].y);
    ctx.lineTo(P[index2].x, P[index2].y);
    ctx.stroke();
}

$(function () {
    // alert("Hello, icecream");
    console.log("document: ", document);
    var h = document.height;
    w = document.width;
    var canvas = document.getElementById('closest');
    canvas.height = 2000;
    canvas.width = 2000;
    
    if(canvas.getContext) {
        var ctx = canvas.getContext('2d');
        console.log(ctx);
        var pointSet = [];
        var i = 0;
        for(i = 0; i < 50; i++) {
            pointSet.push(new Point(Math.random()*2000, Math.random()*2000));
            pointSet[i].drawPoint(ctx);
        }
        console.log(pointSet);
        BruteForceClosestPoints(pointSet, ctx);
        // ctx.fillStyle = "rgb(200, 0, 0)";
        // ctx.fillRect(10, 10, 55, 50);

        // ctx.fillStyle = "rgba(0, 0, 200, 0.5)";
        // ctx.fillRect(30, 30, 55, 50);

    } else {

    }
})

