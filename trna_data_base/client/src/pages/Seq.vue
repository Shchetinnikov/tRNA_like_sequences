<template>
    <h3>Download FASTA-files</h3>
    <hr>
    <div class="fs-5" v-for="seq_name in seq_names">
        <div class="row m-1">
            <div class="col-1">
                <div class="h6 mt-3"> {{ seq_name.toUpperCase() }}:</div>
            </div>
            <div class="col-3">
                <button 
                    type="button" 
                    class="btn btn-outline-dark w-100 m-1"
                    @click="onClick(seq_name + '(+)')"
                >
                    {{ seq_name }}(+)</button>
            </div>
            <div class="col-3">
                <button 
                    type="button" 
                    class="btn btn-outline-dark w-100 m-1"
                    @click="onClick(seq_name + '(-)')"
                >
                    {{ seq_name }}(-)</button>
            </div>
        </div>
    </div>
</template>

<script>
import axios from 'axios';

export default {
    data() {
        return {
            seq_names: [],
        }
    },
    methods: {
        async fetchNames() {
            try {
                const response = await axios.get('http://localhost:5000/api/seq/');
                this.seq_names = response.data;
            } catch (e) {
                alert('Ошибка')
            }
        },
        async onClick(file_name) {
            try {
                const file = file_name + '.fa';
                await axios.get('http://localhost:5000/api/seq/' + file, { responseType: 'blob' })
                    .then((response) => {
                        const blob = new Blob([response.data], { type: 'application/text' });
                        const fileUrl = URL.createObjectURL(blob);
                        const fileLink = document.createElement('a');
                        fileLink.href = fileUrl;
                        fileLink.setAttribute('download', file);
                        document.body.appendChild(fileLink);
                        fileLink.click();
                    });

            } catch (e) {
                alert('Ошибка')
            }
        }
    },
    async mounted() {
        this.loading = true;
        await this.fetchNames();
        this.loading = false;
    }
}
</script>

<style scoped>

</style>