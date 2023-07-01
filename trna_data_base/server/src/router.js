import Router from 'express';
import path from 'path';
import tRNA from './tRNA.js';

const router = new Router();


router.get('/info', async (req, res) => {
    // res.setHeader("Access-Control-Allow-Origin", "*")
    // res.setHeader("Access-Control-Allow-Credentials", "true");
    // res.setHeader("Access-Control-Max-Age", "1800");
    // res.setHeader("Access-Control-Allow-Headers", "content-type");
    // res.setHeader( "Access-Control-Allow-Methods", "PUT, POST, GET, DELETE, PATCH, OPTIONS" ); 
   
    const chr = req.query._filter.chr;
    const trna = req.query._filter.trna;
    const direct = req.query._filter.direct;
    const page = Number(req.query._page);
    const limit = Number(req.query._limit);

    let posts = await tRNA.find({
        $and: [
            { chromosome: chr ? "Homo_sapiens.GRCh38.dna.chromosome." + chr + ".fa" : { $regex: "" } },
            { trna: trna ? trna : {$regex: ""} },
            { direction: direct ? direct : {$regex: ""} }]
    });

    const count = posts.length;

    if (page * limit < count) {
        posts = posts.slice((page - 1) * limit, page * limit);
    } else {
        posts = posts.slice((page - 1) * limit, count);
    }

    return res.status(200).json({
        posts: posts,
        totalCount: count
    });
})

router.get('/main', async (req, res) => {
    let totalCount = 0;
    let trna_counts = {
        Ala: { '+': 0, '-': 0 }, Arg: { '+': 0, '-': 0 }, Asn: { '+': 0, '-': 0 }, Asp: { '+': 0, '-': 0 },
        Cys: { '+': 0, '-': 0 }, Gln: { '+': 0, '-': 0 }, Glu: { '+': 0, '-': 0 }, Gly: { '+': 0, '-': 0 },
        His: { '+': 0, '-': 0 }, Ile: { '+': 0, '-': 0 }, Leu: { '+': 0, '-': 0 }, Lys: { '+': 0, '-': 0 }, 
        Met: { '+': 0, '-': 0 }, Phe: { '+': 0, '-': 0 }, Pro: { '+': 0, '-': 0 }, SeC: { '+': 0, '-': 0 },
        Ser: { '+': 0, '-': 0 }, Sup: { '+': 0, '-': 0 }, Thr: { '+': 0, '-': 0 }, Trp: { '+': 0, '-': 0 },
        Tyr: { '+': 0, '-': 0 }, Val: { '+': 0, '-': 0 }
    };

    for (let key of Object.keys(trna_counts)) {
        await tRNA.countDocuments({
            trna: "trna-" + String(key),
            direction: '+'
        }).then((ans) => {
            trna_counts[key]['+'] = ans
            totalCount += ans
        });
        await tRNA.countDocuments({
            trna: "trna-" + String(key),
            direction: '-'
        }).then((ans) => {
            trna_counts[key]['-'] = ans
            totalCount += ans
        });
    }
    
    return res.status(200).json({
        trna_counts: trna_counts,
        totalCount: totalCount
    });
})

router.get('/seq', async (req, res) => {
    let seq_names;
    await tRNA.find().distinct('trna').then((ans) => seq_names = ans);
    return res.status(200).json(seq_names);
})

router.get('/seq/:file', async (req, res) => {
    const file = req.params.file;
    res.sendFile(path.resolve('data', 'seq', file));
})


export default router;