const express = require("express")
const app = express()


app.use(express.static("./"))

//app.get("/controlLed", (req,res) => {
//    console.log(req.query.LED)
//    console.log(req.query.control)
//    controlLED(req.query.LED1, req.query.control)
//	controlLED(req.query.LED2, req.query.control)
//	controlLED(req.query.LED3, req.query.control)
//	controlLED(req.query.LED4, req.query.control)
//	var response={
//		"LED1":req.query.LED1,
//		"LED2":req.query.LED2,
//		"LED3":req.query.LED3,
//		"LED4":req.query.LED4,
//		"Control":req.query.control,
//	}
 //   res.send("Successfully Requested")
    
//});

app.get("/semaphore_con",(req,res)=>{
    let request =req.query;
    shine(parseInt(request.total_num));
    res.status(200).send("Request Successful !!!");
});


//function controlLED(LED,POWER){
 //  let child_process = require("child_process");
//    let process = child_process.execFile('sudo',[
//        "../nodejs/C++/L2Program",LED,POWER
//    ]);
//    process.stdout.on('data',(data) =>{
//        console.log(`stdout: ${data}`);
//    });
//    process.stdout.on('data',(data) =>{
//        console.error(`stderr: ${data}`);
//    });

//}


let shine=(times)=>{
    let child_process =require("child_process");
    let process = child_process.execFile('make',["semaphore"]);

    
    process.stdout.on('data',(data)=>{
        console.log(`stdout: ${data}`);
    });
    process.stderr.on('data',(data)=>{
        console.error(`stdout: ${data}`);
    });
    
}

// set port,listen for requests
const PORT = process.env.PORT || 8080;
app.listen(PORT,()=>{
    console.log(`Server is running on port ${PORT}.`);
});
