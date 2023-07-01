<template>
    <h3>TRNA gene summary</h3>
    <hr>
    <div v-if="loading">
        <my-loader></my-loader>
    </div>
    <div v-else>
        <div class="fs-5 m-3">        
            <p>A database of RNA sequences was obtained for the human genome Homo sapiens (hg38 - GRCh38.p 13).</p>
            <p>The search was carried out using the HMMER program based on the aligned sequences of the database <a href="http://lowelab.ucsc.edu/GtRNAdb">http://lowelab.ucsc.edu/GtRNAdb</a>. 
            The base sequences were aligned using the T-Coffee algorithm, transferred to the HMMER, and the results were processed.</p>
            <p>The quantitative characteristics of the found sequences are presented below.</p>
        </div>
        <div class="m-5">
            <table class="table mb-5">
            <thead>
                <tr>
                <th scope="col">Type of tRNA</th>
                <th scope="col" v-for="amino_name in Object.keys(this.trna_counts)">{{ amino_name }}</th>
                </tr>
            </thead>
            <tbody>
                <tr>
                    <th scope="row">Count (5'-3')</th>
                    <td v-for="amino_name in Object.keys(this.trna_counts)"> {{ this.trna_counts[amino_name]['+'] }}</td>
                </tr>
                <tr>
                    <th scope="row">Count (3'-5')</th>
                    <td v-for="amino_name in Object.keys(this.trna_counts)"> {{ this.trna_counts[amino_name]['-'] }}</td>
                </tr>
                <tr>
                    <th scope="row">Total</th>
                    <td v-for="amino_name in Object.keys(this.trna_counts)"> {{ this.trna_counts[amino_name]['+'] + this.trna_counts[amino_name]['-'] }}</td>
                </tr>
            </tbody>
            </table>
            <div class="h5">
                Total: {{ this.totalCount }}
            </div>
        </div>
        <div class="fs-5 m-3">
            <div class="h4">Distribution of sequence lengths</div>
            <hr>
            <p>For each type and direction of tRNA, graphs of the distribution of sequence lengths were constructed. 
                From the type of graphs, we can draw conclusions about the average length of the sequence of each group.</p>
            <p>The graphs are presented below.</p>
            <div class="row d-flex justify-content-center m-3">
                <div class="h5">Direction 5'-3'</div>
                <img src="@/../public/dist_dir.png" style="width: 80%;" alt="dist_dir">
            </div>
            <div class="row d-flex justify-content-center m-3">
                <div class="h5">Direction 3'-5'</div>
                <img src="@/../public/dist_inv.png" style="width: 80%;" alt="dist_inv">
            </div>
        </div>
    </div>

</template>

<script>
import axios from 'axios';

export default {
    data() {
        return {
            loading: false,
            totalCount: 0,
            trna_counts: 0,
            directions: ['+', '-'],
        }
    },
    methods: {
        async fetchData() {
            try {
                const response = await axios.get('http://localhost:5000/api/main/');
                // const response = await axios.get('https://jsonplaceholder.typicode.com/posts?_limit=10');
                this.trna_counts = response.data.trna_counts;
                this.totalCount = response.data.totalCount;
            } catch (e) {
                alert('Ошибка')
            }
        },
    },
    async mounted() {
        this.loading = true;
        await this.fetchData();
        this.loading = false;
    }
        
}
</script>

<style scoped>

</style>