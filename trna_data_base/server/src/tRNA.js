import mongoose from "mongoose";

const tRNASchema = new mongoose.Schema({
    chromosome: String,
    trna: String,
    seq: String,
    direction: String,
    start_idx: Number,
    end_idx: Number,
    e_value: Number
});

export default mongoose.model('tRNA', tRNASchema);