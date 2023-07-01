<template>
    <div class="post">
        <div class="row small">
            <div class="col-2 overflow-auto">
                {{ post.chromosome.split('.fa')[0].split('dna.')[1] }}
            </div>
            <div class="col-1 overflow-auto">
                {{ post.trna }}
            </div>
            <div class="col-4 overflow-auto">
                {{ post.seq}}
            </div> 
            <div class="col-1 overflow-auto" style="display: flex; justify-content: center;">
                {{ post.direction }}
            </div>
            <div class="col-1 overflow-auto">
                {{ post.start_idx }}
            </div>
            <div class="col-1 overflow-auto">
                {{ post.end_idx }}
            </div>
            <div class="col-1 overflow-auto">
                {{ post.e_value }}
            </div>
        </div>
    </div>
</template>

<script>
export default {
    props: {
        post: {
            type: Object,
            required: true,
        }
    },
}
</script>

<style scoped>
.post {
    padding: 10px 10px;
    border: 1px solid rgb(125, 119, 119);
    margin: 0.5px;
}

</style>