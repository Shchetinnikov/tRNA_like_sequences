import dotenv from 'dotenv';
import express from 'express';
// import fileUpload from 'express-fileupload';
import mongoose from 'mongoose';
import router from './router.js';
import cors from 'cors';


dotenv.config();
const PORT = process.env.PORT;

const app = express();

// app.use(fileUpload({}))
app.use(cors());
app.use(express.json());
app.use('/api', router);


async function startUp() {
    try {
        await mongoose.connect('mongodb://127.0.0.1:27017/GenomicDB');
        app.listen(PORT, () => { console.log(`Server has been started on port ${PORT}`)})
    } catch (e) {
        console.log(e);
    }
}

startUp()