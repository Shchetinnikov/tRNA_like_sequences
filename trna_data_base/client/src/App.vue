<template>
    <div class="app">
        <Header></Header>
    
        <main>
            <div class="row">
                <div class="col-2  bg-secondary">
                    <Sidebar></Sidebar>
                </div>
                <div class="col-10">
                    <router-view></router-view>
                </div>
            </div>

        </main>

        <footer class="bg-secondary text-white">
            <div class="row">
                <div class="d-flex justify-content-center">Student: Shchetinnikov Konstantin</div>
            </div>
            <div class="row">
                <div class="d-flex justify-content-center">Scientific advisor: Korotkov Eugene</div>
            </div>
            <div class="row">
                <div class="d-flex justify-content-center">National Research Nuclear University "MEPhI"</div>
            </div>
        </footer>

    </div>
</template>

<script>
import Header from '@/components/Header.vue'
import Sidebar from '@/components/Sidebar.vue'

export default {
    components: {
        Header, Sidebar
    },

}
</script>

<style scoped>

</style>