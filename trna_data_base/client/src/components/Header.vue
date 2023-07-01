<template>
    <header>
        <div class="container m-4 my-5">
            <div class="row">
                <div class="col-3">
                    <img src="@/../public/logo.jpg" style="width: 70%;" alt="logo">
                </div>
                <div class="col-9 d-flex flex-column justify-content-center text-left">
                    <h1 class="text-uppercase">{{ source_name }}</h1>
                    <h4>{{ source_descr }}</h4>
                </div>
                
            </div>
        </div>
    </header>
</template>

<script>
export default {
    data() {
        return {
            source_name: "Genomic tRNA Database",
            source_descr: "Homo sapiens (hg38 - GRCh38.p13)",
        }
    }
}
</script>

<style scoped>

</style>