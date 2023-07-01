import mongoose from 'mongoose';
import fs from 'fs';
import path from 'path';

// All files
const db_dir = "../../db";
const files_names = [];

fs.readdirSync(db_dir).forEach(file => {
    files_names.push(file);
});


// Create objects
let objs = [];
for (let file_name of files_names) {
    let text = fs.readFileSync(path.resolve(db_dir, file_name), 'utf-8');
    let lines = text.split('\n');
    for (let i = 1; i < lines.length; i += 2) {
        const line = lines[i].split(' ');
        const obj = {
            chromosome: line[0],
            trna: line[1].split('(')[0],
            seq: line[2],
            direction: line[1].split('(')[1].split(')')[0],
            start_idx: line[4],
            end_idx: line[5],
            e_value: line[3]
        }
        objs.push(obj);
    }
}

console.log(objs.slice(0, 10));

// // Fill in database
// async function fillIn() {
//     await mongoose.connect('mongodb://127.0.0.1:27017/GenomicDB');
//     const tRNASchema = new mongoose.Schema({
//         chromosome: String,
//         trna: String,
//         seq: String,
//         direction: String,
//         start_idx: Number,
//         end_idx: Number,
//         e_value: Number
//     });
//     const tRNA = mongoose.model('tRNA', tRNASchema);

//     for (const obj of objs) {
//         const trna = new tRNA(obj)
//         await trna.save();
//     }

// }

// fillIn().catch(err => console.log(err));