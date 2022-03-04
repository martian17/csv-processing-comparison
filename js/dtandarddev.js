const fs = require("fs");



const readLine = function(path,processLine){
    return new Promise((res,rej)=>{
        const readableStream = fs.createReadStream(path);

        readableStream.on('error', function (err) {
            rej(err);
        });

        let line = "";
        let progress = 0;

        readableStream.on('data', (chunk) => {
            progress += chunk.length;
            let str = chunk.toString();
            let ll = str.split("\n");
            line += ll[0];
            if(ll.length > 1){
                processLine(line,progress);
            }
            for(let i = 1; i < ll.length-1; i++){
                processLine(ll[i],progress);
            }
            if(ll.length > 1){
                line = ll[ll.length-1];
            }
        });

        readableStream.on('end', () => {
            if(line !== "")processLine(line,progress);
            res();
        });
    });
};



const main = async function(){
    let path = "../test.csv";
    let n = 0;
    let sum = 0;
    let sqsum = 0;
    let stats = fs.statSync(path);
    console.log(`file size: ${stats.size}`);
    console.log("");
    await readLine(path,(line,progress)=>{
        if(n%10000 === 0){
            console.log("\033[F"+`progress: ${((progress/stats.size*100)+"00000000").slice(0,5)}%`);
        }
        if(n === 0){
            n++;
            return;//ignore the first row
        }
        let [a,b] = line.split(",");
        a = parseFloat(a);
        sum += a;
        sqsum += a*a;
        n++;
    });
    let mean = sum / n;
    let variance = sqsum / n - mean * mean;
    let stddev = Math.sqrt(variance);
    console.log(`stddev is: ${stddev}`);
};

main();